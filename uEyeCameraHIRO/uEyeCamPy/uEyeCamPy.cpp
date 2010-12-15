#include <Python.h>
#include <assert.h>

#include <uEye.h>
#include "uEyeCamera.h"

#define MODULESTR "uEyeCam"

static PyObject *opencv_error;

struct ueyecamera_t {
  PyObject_HEAD
  uEyeCamera *a;
};

struct iplimage_t {
  PyObject_HEAD
  IplImage *a;
  PyObject *data;
  size_t offset;
};

struct cvmat_t {
  PyObject_HEAD
  CvMat *a;
  PyObject *data;
  size_t offset;
};

struct cvmatnd_t {
  PyObject_HEAD
  CvMatND *a;
  PyObject *data;
  size_t offset;
};

typedef IplImage ROIplImage;

static int is_iplimage(PyObject *o);
static int convert_to_IplImage(PyObject *o, IplImage **dst, const char *name = "no_name");
static void translate_error_to_exception(void)
{
  PyErr_SetString(opencv_error, cvErrorStr(cvGetErrStatus()));
  cvSetErrStatus(0);
}

#define ERRCHK do { if (cvGetErrStatus() != 0) { translate_error_to_exception(); return NULL; } } while (0)
#define ERRWRAP(F) do { try { F; } catch (const cv::Exception &e) { PyErr_SetString(opencv_error, e.err.c_str()); return NULL; } ERRCHK; } while(0)


/**
* エラーメッセージ表示
*/
static int failmsg(const char *fmt, ...)
{
  char str[1000];

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(str, sizeof(str), fmt, ap);
  va_end(ap);

  PyErr_SetString(PyExc_TypeError, str);
  return 0;
}



// iplimage
/** 
* iplimageデストラクタ
*/
static void iplimage_dealloc(PyObject *self)
{
  iplimage_t *pc = (iplimage_t*)self;
  cvReleaseImageHeader((IplImage**)&pc->a);
  Py_DECREF(pc->data);
  PyObject_Del(self);
}

/**
* iplimageのrepr()
*/
static PyObject *iplimage_repr(PyObject *self)
{
  iplimage_t *cva = (iplimage_t*)self;
  IplImage* ipl = (IplImage*)(cva->a);
  char str[1000];
  sprintf(str, "<iplimage(");
  char *d = str + strlen(str);
  sprintf(d, "nChannels=%d ", ipl->nChannels);
  d += strlen(d);
  sprintf(d, "width=%d ", ipl->width);
  d += strlen(d);
  sprintf(d, "height=%d ", ipl->height);
  d += strlen(d);
  sprintf(d, "widthStep=%d ", ipl->widthStep);
  d += strlen(d);
  sprintf(d, ")>");
  return PyString_FromString(str);
}

/**
* iplimage から string オブジェクトへの変換
*/
static PyObject *iplimage_tostring(PyObject *self, PyObject *args)
{
  iplimage_t *pc = (iplimage_t*)self;
  IplImage *i;
  if (!convert_to_IplImage(self, &i, "self"))
    return NULL;
  if (i == NULL)
    return NULL;
  int bps;
  switch (i->depth) {
  case IPL_DEPTH_8U:
  case IPL_DEPTH_8S:
    bps = 1;
    break;
  case IPL_DEPTH_16U:
  case IPL_DEPTH_16S:
    bps = 2;
    break;
  case IPL_DEPTH_32S:
  case IPL_DEPTH_32F:
    bps = 4;
    break;
  case IPL_DEPTH_64F:
    bps = 8;
    break;
  default:
    return (PyObject*)failmsg("Unrecognised depth %d", i->depth);
  }
  int bpl = i->width * i->nChannels * bps;
  if (bpl == i->widthStep && pc->offset == 0) {
    Py_INCREF(pc->data);
    return pc->data;
  } else {
    int l = bpl * i->height;
    char *s = new char[l];
    int y;
    for (y = 0; y < i->height; y++) {
      memcpy(s + y * bpl, i->imageData + y * i->widthStep, bpl);
    }
    PyObject *r = PyString_FromStringAndSize(s, l);
    delete s;
    return r;
  }
}

/**
* iplimage のメソッド
*/
static struct PyMethodDef iplimage_methods[] =
  {
    {"tostring", iplimage_tostring, METH_VARARGS},
    {NULL,          NULL}
  };

/// getter, setter
static PyObject *iplimage_getnChannels(iplimage_t *cva)
{
  return PyInt_FromLong(((IplImage*)(cva->a))->nChannels);
}
static PyObject *iplimage_getwidth(iplimage_t *cva)
{
  return PyInt_FromLong(((IplImage*)(cva->a))->width);
}
static PyObject *iplimage_getheight(iplimage_t *cva)
{
  return PyInt_FromLong(((IplImage*)(cva->a))->height);
}
static PyObject *iplimage_getdepth(iplimage_t *cva)
{
  return PyInt_FromLong(((IplImage*)(cva->a))->depth);
}
static PyObject *iplimage_getorigin(iplimage_t *cva)
{
  return PyInt_FromLong(((IplImage*)(cva->a))->origin);
}
static void iplimage_setorigin(iplimage_t *cva, PyObject *v)
{
  ((IplImage*)(cva->a))->origin = PyInt_AsLong(v);
}

static PyGetSetDef iplimage_getseters[] = {
  {(char*)"nChannels", (getter)iplimage_getnChannels, (setter)NULL, (char*)"nChannels", NULL},
  {(char*)"width", (getter)iplimage_getwidth, (setter)NULL, (char*)"width", NULL},
  {(char*)"height", (getter)iplimage_getheight, (setter)NULL, (char*)"height", NULL},
  {(char*)"depth", (getter)iplimage_getdepth, (setter)NULL, (char*)"depth", NULL},
  {(char*)"origin", (getter)iplimage_getorigin, (setter)iplimage_setorigin, (char*)"origin", NULL},
  {NULL}  // Sentinel
};

/**
* iplimage_Type構造体
*/
static PyTypeObject iplimage_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,                                      /*size*/
  MODULESTR".iplimage",                   /*name*/
  sizeof(iplimage_t),                     /*basicsize*/
};

/**
* iplimage オブジェクトにメソッド追加
*/
static void iplimage_specials(void)
{
  iplimage_Type.tp_dealloc = iplimage_dealloc;
  iplimage_Type.tp_repr = iplimage_repr;
  iplimage_Type.tp_methods = iplimage_methods;
  iplimage_Type.tp_getset = iplimage_getseters;
}

/**
* iplimage の判定
*/ 
static int is_iplimage(PyObject *o)
{
  return PyType_IsSubtype(o->ob_type, &iplimage_Type);
}


/// uEyeCamera
/**
* uEyeCamera 構造体デストラクタ
*/
static void ueyecamera_dealloc(PyObject *self)
{
  ueyecamera_t *pu = (ueyecamera_t*)self;
  pu->a->close();
  delete pu->a;
  PyObject_Del(self);
}

/**
* uEyeCamera_Type構造体
*/
static PyTypeObject ueyecamera_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  0,                                      /*size*/
  MODULESTR".ueyecamera",                 /*name*/
  sizeof(ueyecamera_t),                   /*basicsize*/
};

/**
* ueyecamera オブジェクトにメソッド追加
*/
static void ueyecamera_specials(void)
{
  ueyecamera_Type.tp_dealloc = ueyecamera_dealloc;
}

/**
* pythonオブジェクトから IplImageオブジェクトへの変換
*/
static int convert_to_IplImage(PyObject *o, IplImage **dst, const char *name)
{
  iplimage_t *ipl = (iplimage_t*)o;
  void *buffer;
  Py_ssize_t buffer_len;

  if (!is_iplimage(o)) {
    return failmsg("Argument '%s' must be IplImage", name);
  } else if (PyString_Check(ipl->data)) {
    cvSetData(ipl->a, PyString_AsString(ipl->data) + ipl->offset, ipl->a->widthStep);
    assert(cvGetErrStatus() == 0);
    *dst = ipl->a;
    return 1;
  } else if (ipl->data && PyObject_AsWriteBuffer(ipl->data, &buffer, &buffer_len) == 0) {
    cvSetData(ipl->a, (void*)((char*)buffer + ipl->offset), ipl->a->widthStep);
    assert(cvGetErrStatus() == 0);
    *dst = ipl->a;
    return 1;
  } else {
    return failmsg("IplImage argument '%s' has no data", name);
  }
}

/**
* ints（Vector<int>みたいな）
*/ 
struct ints {
  int *i;
  int count;
};

/**
* intsへの変換
*/
static int convert_to_ints(PyObject *o, ints *dst, const char *name = "no_name")
{
  PyObject *fi = PySequence_Fast(o, name);
  if(fi == NULL)
    return 0;

  dst->count = PySequence_Fast_GET_SIZE(fi);
  dst->i = new int[dst->count];
  for(Py_ssize_t i = 0; i < PySequence_Fast_GET_SIZE(fi); i++) {
    PyObject *item = PySequence_Fast_GET_ITEM(fi, i);
    dst->i[i] = PyInt_AsLong(item);
  }
  Py_DECREF(fi);
  return 1;
}

/**
* uEyeCamera構造体へのポインタへの変換
*/
static int convert_to_uEyeCameraPTR(PyObject *o, uEyeCamera** dst, const char *name = "no_name")
{
  if (PyType_IsSubtype(o->ob_type, &ueyecamera_Type)) {
    *dst = ((ueyecamera_t*)o)->a;
    return 1;
  } else {
    (*dst) = (uEyeCamera*)NULL;
    return failmsg("Expected CvCapture for argument '%s'", name);
  }
}

/************************************************************************/

#define FROM_double(r)  PyFloat_FromDouble(r)
#define FROM_float(r)  PyFloat_FromDouble(r)
#define FROM_int(r)  PyInt_FromLong(r)
#define FROM_unsigned(r)  PyLong_FromUnsignedLong(r)

/**
* uEyeCamera構造体へのポインタからpythonオブジェクトへの変換
*/
static PyObject *FROM_uEyeCameraPTR(uEyeCamera *r)
{
  ueyecamera_t *c = PyObject_NEW(ueyecamera_t, &ueyecamera_Type);
  c->a = r;
  return (PyObject*)c;
}

typedef float CvMatr32f_i[9];

static PyObject *FROM_ROIplImagePTR(ROIplImage *r)
{
  if (r != NULL) {
    iplimage_t *cva = PyObject_NEW(iplimage_t, &iplimage_Type);
    cva->a = cvCreateImageHeader(cvSize(100,100), 8, 1);
    *(cva->a) = *r;
    cva->data = PyBuffer_FromReadWriteMemory(r->imageData, r->height * r->widthStep);
    cva->offset = 0;
    return (PyObject*)cva;
  } else {
    Py_RETURN_NONE;
  }
}

/************************************************************************/

/// uEyeCam メソッド

/**
* キャプチャ画像サイズの変更
*/
static PyObject *pySetImageSize(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int width, height, cam=-1;
  ints cams;

  if(!PyArg_ParseTuple(args, "Oi(ii):pySetImageSize(int)", &pyobj_capture, &cam, &width, &height)) {
    PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&(ii):pySetImageSize(list)", &pyobj_capture, convert_to_ints, &cams, &width, &height))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setImageSize(cam, width, height);
  } else {
    for(int i=0; i<cams.count; i++) {
      ret |= ucam->setImageSize(cams.i[i], width, height);
    }
  }
  return FROM_int(ret);
}

/**
* キャプチャ画像位置の変更
*/
static PyObject *pySetImagePos(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int x, y, cam=-1;
  ints cams;

  if(!PyArg_ParseTuple(args, "Oi(ii):pySetImagePos(int)", &pyobj_capture, &cam, &x, &y)) {
    PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&(ii):pySetImagePos(list)", &pyobj_capture, convert_to_ints, &cams, &x, &y))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera"))
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setImagePos(cam, x, y);
  } else {
    for(int i=0; i<cams.count; i++) {
      ret |= ucam->setImagePos(cams.i[i], x, y);
    }
  }
  return FROM_int(ret);
}

/**
* AOI（Area of Interest）の変更
*/
static PyObject *pySetImageAOI(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int x, y, width, height, cam=-1;
  ints cams;

  if(!PyArg_ParseTuple(args, "Oi(iiii):pySetImagePos(int)", &pyobj_capture, &cam, &x, &y, &width, &height)) {
    PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&(iiii):pySetImagePos(list)", &pyobj_capture, convert_to_ints, &cams, &x, &y, &width, &height))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera"))
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setImageAOI(cam, x, y, width, height);
  } else {
    for(int i=0; i<cams.count; i++) {
      ret |= ucam->setImageAOI(cams.i[i], x, y, width, height);
    }
  }
  return FROM_int(0);
}

/**
* SubSampling の設定
*/
static PyObject *pySetSubSampling(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int cam=-1;
  ints cams;
  int modex, modey;

  if(!PyArg_ParseTuple(args, "Oi(ii)", &pyobj_capture, &cam, &modex, &modey)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&(ii)", &pyobj_capture, convert_to_ints, &cams, &modex, &modey))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setSubSampling(cam, modex, modey);
  } else {
    for(int i=0; i<cams.count; i++) {
      ret |= ucam->setSubSampling(cams.i[i], modex, modey);
    }
  }
  return FROM_int(ret);
}

/**
* Binning の設定
*/
static PyObject *pySetBinning(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int binx, biny, cam=-1;
  ints cams;

  if(!PyArg_ParseTuple(args, "Oi(ii)", &pyobj_capture, &cam, &binx, &biny)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&(ii)", &pyobj_capture, convert_to_ints, &cams, &binx, &biny))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setBinning(cam, binx, biny);
  } else {
    for(int i=0; i<cams.count; i++) {
      ret |= ucam->setBinning(cams.i[i], binx, biny);
    }
  }
  return FROM_int(ret);
}

/**
* Autoパラメータの設定
*/
static PyObject *pySetAutoParameter(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int param, cam=-1;
  ints cams;
  double val1, val2;

  if(!PyArg_ParseTuple(args, "Oi(idd)", &pyobj_capture, &cam, &param, &val1, &val2)) {
    PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&(idd)", &pyobj_capture, convert_to_ints, &cams, &param, &val1, &val2))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setAutoParameter(cam, param, &val1, &val2);
  } else {
    for(int i=0; i<cams.count; i++)
      ret |= ucam->setAutoParameter(cams.i[i], param, &val1, &val2);
  }

  return FROM_int(ret);
}

/**
* パラメータの保存
*/
static PyObject *pySaveParameter(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int cam = -1;
  ints cams;
  char *filename = NULL;
  char filename_new[512];

  if(!PyArg_ParseTuple(args, "Ois:pySaveParameter(int)", &pyobj_capture, &cam, &filename)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&s:pySaveParameter(list)", &pyobj_capture, convert_to_ints, &cams, &filename))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
	ret = ucam->saveParameter(cam, filename);
  } else {
	for(int i=0; i<cams.count; i++) {
      snprintf(filename_new, 512, "%d%s", i, filename);
	  ret |= ucam->saveParameter(cams.i[i], filename_new);
	}
  }

  return FROM_int(ret);
}

/**
* パラメータの読み込み
*/
static PyObject *pyLoadParameter(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int cam = -1;
  ints cams;
  char *filename = NULL;
  char filename_new[512];

  if(!PyArg_ParseTuple(args, "Ois:pyLoadParameter(int)", &pyobj_capture, &cam, &filename)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&s:pyLoadParameter(list)", &pyobj_capture, convert_to_ints, &cams, &filename))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
	ret = ucam->loadParameter(cam, filename);
  } else {
	for(int i=0; i<cams.count; i++) {
      snprintf(filename_new, 512, "%d%s", i, filename);
	  ret |= ucam->loadParameter(cams.i[i], filename_new);
	}
  }

  return FROM_int(ret);
}

/**
* FPSの取得
*/
static PyObject *pyGetFPS(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int cam = -1;
  ints cams;
  PyObject *pr;

  if(!PyArg_ParseTuple(args, "Oi:pyGetFPS(int)", &pyobj_capture, &cam)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&:pyGetFPS(list)", &pyobj_capture, convert_to_ints, &cams))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  double fps;
  if(cam>=0) {
    fps = ucam->getFPS(cam);
    return FROM_double(fps);
  } else if(cams.count==1){
	fps = ucam->getFPS(cams.i[0]);
    return FROM_double(fps);
  } else {
    pr = PyList_New(cams.count);
	for(int i=0; i<cams.count; i++) {
	  fps = ucam->getFPS(cams.i[i]);
      PyList_SetItem(pr, i, FROM_double(fps));
	}
	return pr;
  }
}

/**
* FPSの設定
*/
static PyObject *pySetFPS(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int cam = -1;
  ints cams;
  double fps;
  PyObject *pr;

  if(!PyArg_ParseTuple(args, "Oif:pySetFPS(int)", &pyobj_capture, &cam, &fps)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&f:pySetFPS(list)", &pyobj_capture, convert_to_ints, &cams, &fps))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  double new_fps;
  if(cam>=0) {
    new_fps = ucam->setFPS(cam, fps);
    return FROM_double(fps);
  } else if(cams.count==1){
	new_fps = ucam->setFPS(cams.i[0], fps);
    return FROM_double(fps);
  } else {
    pr = PyList_New(cams.count);
	for(int i=0; i<cams.count; i++) {
	  new_fps = ucam->setFPS(cams.i[i], fps);
      PyList_SetItem(pr, i, FROM_double(new_fps));
	}
	return pr;
  }
}

/**
* PixelClockの設定
*/
static PyObject *pySetPixelClock(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  int cam = -1;
  ints cams;
  int pclock;

  if(!PyArg_ParseTuple(args, "Oii:pySetPixelClock(int)", &pyobj_capture, &cam, &pclock)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&i:pySetPixelClock(list)", &pyobj_capture, convert_to_ints, &cams, &pclock))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera")) 
    return NULL;

  int ret = 0;
  if(cam>=0) {
    ret = ucam->setPixelClock(cam, pclock);
  } else {
	for(int i=0; i<cams.count; i++) {
	  ret |= ucam->setPixelClock(cams.i[i], pclock);
	}
  }

  return FROM_int(ret);
}

/**
* uEyeCameraオブジェクト生成
*/
static PyObject *pyCaptureFromuEye(PyObject *self, PyObject *args)
{
  uEyeCamera *r;
  ERRWRAP(r = new uEyeCamera);

  return FROM_uEyeCameraPTR(r);
}

/**
* 画像キャプチャ
*/
static PyObject *pyQueryFrame(PyObject *self, PyObject *args)
{
  uEyeCamera* ucam=NULL;
  PyObject *pyobj_capture = NULL;
  ints cams;
  int cam=-1;
  PyObject *pr;

  if(!PyArg_ParseTuple(args, "Oi:pyQueryFrame(int)", &pyobj_capture, &cam)) {
	PyErr_Clear();
    if(!PyArg_ParseTuple(args, "OO&:pyQueryFrame(list)", &pyobj_capture, convert_to_ints, (void*)&cams))
      return NULL;
  }
  if(!convert_to_uEyeCameraPTR(pyobj_capture, &ucam, "uEyeCamera"))
    return NULL;

  IplImage* r =NULL;
  if(cam>=0) {
    ERRWRAP(r = &IplImage(ucam->queryFrame(cam)));
    return iplimage_tostring(FROM_ROIplImagePTR(r), NULL);
  } else if(cams.count==1) {
    ERRWRAP(r = &IplImage(ucam->queryFrame(cams.i[0])));
    return iplimage_tostring(FROM_ROIplImagePTR(r), NULL);
  } else {
    pr = PyList_New(cams.count);
    for(int i=0; i<cams.count; i++) {
      ERRWRAP(r = &IplImage((ucam->queryFrame(cams.i[i]))));
      PyList_SetItem(pr, i, iplimage_tostring(FROM_ROIplImagePTR(r), NULL));
    }
    return pr;
  }
}



/************************************************************************/

/// メソッドのエクスポート
static PyMethodDef methods[] = {

  {"QueryFrame", pyQueryFrame, METH_VARARGS, "query frame"},
  {"CaptureFromUEYE", pyCaptureFromuEye, METH_VARARGS, "capture"},
//  {"Open", pyOpen, METH_VARARGS, "Open()"},
  {"SetImageSize", pySetImageSize, METH_VARARGS, "SetImageSize(cap, cam, (width, height))"},
  {"SetImagePos", pySetImagePos, METH_VARARGS, "SetImagePos(cap, cam, (x, y))"},
  {"SetImageAOI", pySetImageAOI, METH_VARARGS, "SetImageAOI(cap, cam, (x, y, width, height))"},
  {"SetBinning", pySetBinning, METH_VARARGS, "SetBinning(cap, cam, (binx, biny))"},
  {"SetAutoParameter", pySetAutoParameter, METH_VARARGS, "SetAutoParameter(cap, cam, param, val1, val2)"},
  {"SaveParameter", pySaveParameter, METH_VARARGS, "SaveParameter(cap, cam, filename)"},
  {"LoadParameter", pyLoadParameter, METH_VARARGS, "LoadParameter(cap, cam, filename)"},
  {"GetFPS", pyGetFPS, METH_VARARGS, "GetFPS(cap, cam)"},
  {"SetFPS", pySetFPS, METH_VARARGS, "SetFPS(cap, cam, fps)"},
  {"SetPixelClock", pySetPixelClock, METH_VARARGS, "SetPixelClock(cap, cam, pclock)"},
  {"SetSubSampling", pySetSubSampling, METH_VARARGS, "SetSubSampling(cap, cam, (modex, modey))"},

  {NULL, NULL},
};

/************************************************************************/
/* Module init */

static int to_ok(PyTypeObject *to)
{
  to->tp_alloc = PyType_GenericAlloc;
  to->tp_new = PyType_GenericNew;
  to->tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
  return (PyType_Ready(to) == 0);
}

#define MKTYPE(NAME)  do { NAME##_specials(); if (!to_ok(&NAME##_Type)) return; } while (0)

extern "C"
#if defined WIN32 || defined _WIN32
__declspec(dllexport)
#endif
void inituEyeCam()
{
  PyObject *m, *d;

  cvSetErrMode(CV_ErrModeParent);

  MKTYPE(iplimage);
  MKTYPE(ueyecamera);

  m = Py_InitModule(MODULESTR"", methods);
  d = PyModule_GetDict(m);

  opencv_error = PyErr_NewException((char*)MODULESTR".error", NULL, NULL);
  PyDict_SetItemString(d, "error", opencv_error);

#define PUBLISH(I) PyDict_SetItemString(d, #I, PyInt_FromLong(I))

/// 定数のエクスポート
#if defined WIN32 || defined _WIN32
  PUBLISH(IS_BINNING_6X_VERTICAL);
  PUBLISH(IS_BINNING_6X_HORIZONTAL);
  PUBLISH(IS_BINNING_8X_VERTICAL);
  PUBLISH(IS_BINNING_8X_HORIZONTAL);
  PUBLISH(IS_BINNING_16X_VERTICAL);
  PUBLISH(IS_BINNING_16X_HORIZONTAL);
  PUBLISH(IS_GET_BINNING_FACTOR_VERTICAL);
  PUBLISH(IS_SET_ENABLE_AUTO_SENSOR_GAIN);
  PUBLISH(IS_GET_ENABLE_AUTO_SENSOR_GAIN);
  PUBLISH(IS_SET_ENABLE_AUTO_SENSOR_SHUTTER);
  PUBLISH(IS_GET_ENABLE_AUTO_SENSOR_SHUTTER);
  PUBLISH(IS_SET_ENABLE_AUTO_FRAMERATE);
  PUBLISH(IS_GET_ENABLE_AUTO_FRAMERATE);
  PUBLISH(IS_SET_AUTO_HYSTERESIS); 
  PUBLISH(IS_GET_AUTO_HYSTERESIS); 
  PUBLISH(IS_GET_AUTO_HYSTERESIS_RANGE); 
  PUBLISH(IS_SET_AUTO_SKIPFRAMES); 
  PUBLISH(IS_GET_AUTO_SKIPFRAMES); 
  PUBLISH(IS_GET_AUTO_SKIPFRAMES_RANGE); 
  PUBLISH(IS_SET_AUTO_WB_HYSTERESIS); 
  PUBLISH(IS_GET_AUTO_WB_HYSTERESIS); 
  PUBLISH(IS_GET_AUTO_WB_HYSTERESIS_RANGE);
  PUBLISH(IS_SET_AUTO_WB_SKIPFRAMES); 
  PUBLISH(IS_GET_AUTO_WB_SKIPFRAMES); 
  PUBLISH(IS_GET_AUTO_WB_SKIPFRAMES_RANGE);
  PUBLISH(IS_SET_ENABLE_AUTO_SENSOR_FRAMERATE);
  PUBLISH(IS_GET_ENABLE_AUTO_SENSOR_FRAMERATE);
  PUBLISH(IS_SUBSAMPLING_6X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_8X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_16X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_6X_HORIZONTAL);
  PUBLISH(IS_SUBSAMPLING_8X_HORIZONTAL);
  PUBLISH(IS_SUBSAMPLING_16X_HORIZONTAL);
#endif

  PUBLISH(IS_BINNING_DISABLE);
  PUBLISH(IS_BINNING_2X_VERTICAL);
  PUBLISH(IS_BINNING_3X_VERTICAL);
  PUBLISH(IS_BINNING_4X_VERTICAL);
  PUBLISH(IS_BINNING_5X_VERTICAL);
  PUBLISH(IS_BINNING_2X_HORIZONTAL);
  PUBLISH(IS_BINNING_3X_HORIZONTAL);
  PUBLISH(IS_BINNING_4X_HORIZONTAL);
  PUBLISH(IS_BINNING_5X_HORIZONTAL);
  PUBLISH(IS_SUBSAMPLING_DISABLE);
  PUBLISH(IS_SUBSAMPLING_2X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_3X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_4X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_5X_VERTICAL);
  PUBLISH(IS_SUBSAMPLING_2X_HORIZONTAL);
  PUBLISH(IS_SUBSAMPLING_3X_HORIZONTAL);
  PUBLISH(IS_SUBSAMPLING_4X_HORIZONTAL);
  PUBLISH(IS_SUBSAMPLING_5X_HORIZONTAL);
  PUBLISH(IS_GET_SUBSAMPLING);
  PUBLISH(IS_GET_SUBSAMPLING_TYPE);
  PUBLISH(IS_GET_SUPPORTED_SUBSAMPLING);

  PUBLISH(IS_GET_BINNING);
  PUBLISH(IS_SET_ENABLE_AUTO_GAIN);
  PUBLISH(IS_GET_ENABLE_AUTO_GAIN);
  PUBLISH(IS_SET_ENABLE_AUTO_SHUTTER);
  PUBLISH(IS_GET_ENABLE_AUTO_SHUTTER); 
  PUBLISH(IS_SET_ENABLE_AUTO_WHITEBALANCE);
  PUBLISH(IS_GET_ENABLE_AUTO_WHITEBALANCE);
  PUBLISH(IS_SET_AUTO_REFERENCE); 
  PUBLISH(IS_GET_AUTO_REFERENCE); 
  PUBLISH(IS_SET_AUTO_GAIN_MAX); 
  PUBLISH(IS_GET_AUTO_GAIN_MAX); 
  PUBLISH(IS_SET_AUTO_SHUTTER_MAX); 
  PUBLISH(IS_GET_AUTO_SHUTTER_MAX); 
  PUBLISH(IS_SET_AUTO_SPEED); 
  PUBLISH(IS_GET_AUTO_SPEED); 
  PUBLISH(IS_SET_AUTO_BRIGHTNESS_ONCE); 
  PUBLISH(IS_GET_AUTO_BRIGHTNESS_ONCE); 
  PUBLISH(IS_SET_AUTO_WB_OFFSET); 
  PUBLISH(IS_GET_AUTO_WB_OFFSET); 
  PUBLISH(IS_SET_AUTO_WB_GAIN_RANGE); 
  PUBLISH(IS_GET_AUTO_WB_GAIN_RANGE); 
  PUBLISH(IS_SET_AUTO_WB_SPEED); 
  PUBLISH(IS_GET_AUTO_WB_SPEED); 
  PUBLISH(IS_SET_AUTO_WB_ONCE); 
  PUBLISH(IS_GET_AUTO_WB_ONCE); 
  PUBLISH(IS_DEFAULT_AUTO_BRIGHT_REFERENCE); 
  PUBLISH(IS_MIN_AUTO_BRIGHT_REFERENCE); 
  PUBLISH(IS_MAX_AUTO_BRIGHT_REFERENCE); 
  PUBLISH(IS_DEFAULT_AUTO_SPEED);
  PUBLISH(IS_MAX_AUTO_SPEED); 
  PUBLISH(IS_DEFAULT_AUTO_WB_OFFSET); 
  PUBLISH(IS_MIN_AUTO_WB_OFFSET); 
  PUBLISH(IS_MAX_AUTO_WB_OFFSET); 
  PUBLISH(IS_DEFAULT_AUTO_WB_SPEED); 
  PUBLISH(IS_MIN_AUTO_WB_SPEED); 
  PUBLISH(IS_MAX_AUTO_WB_SPEED); 
  PUBLISH(IS_SUCCESS); 
  PUBLISH(IS_NO_SUCCESS); 

  PUBLISH(IS_GET_PIXEL_CLOCK);
  PUBLISH(IS_GET_DEFAULT_PIXEL_CLK);
  PUBLISH(IS_GET_FRAMERATE);
  PUBLISH(IS_GET_DEFAULT_FRAMERATE);


}

