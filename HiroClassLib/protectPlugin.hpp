// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __protectPlugin_hh__
#define __protectPlugin_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_protectPlugin
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_protectPlugin
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_protectPlugin
#endif



#ifndef __OpenHRPCommon_hh_EXTERNAL_GUARD__
#define __OpenHRPCommon_hh_EXTERNAL_GUARD__
#include <OpenHRPCommon.hpp>
#endif
#ifndef __HRPcontroller_hh_EXTERNAL_GUARD__
#define __HRPcontroller_hh_EXTERNAL_GUARD__
#include <HRPcontroller.hpp>
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE protectPluginTypes

_CORBA_MODULE_BEG

  typedef ::CORBA::Long LngArray4[4];
  typedef ::CORBA::Long LngArray4_slice;

  _CORBA_MODULE_INLINE LngArray4_slice* LngArray4_alloc() {
    return new LngArray4_slice[4];
  }

  _CORBA_MODULE_INLINE LngArray4_slice* LngArray4_dup(const LngArray4_slice* _s) {
    if (!_s) return 0;
    LngArray4_slice* _data = LngArray4_alloc();
    if (_data) {
      for (_CORBA_ULong _0i0 = 0; _0i0 < 4; _0i0++){
        
        _data[_0i0] = _s[_0i0];

      }
  
    }
    return _data;
  }

  _CORBA_MODULE_INLINE void LngArray4_copy(LngArray4_slice* _to, const LngArray4_slice* _from){
    for (_CORBA_ULong _0i0 = 0; _0i0 < 4; _0i0++){
      
      _to[_0i0] = _from[_0i0];

    }
  
  }

  _CORBA_MODULE_INLINE void LngArray4_free(LngArray4_slice* _s) {
      delete [] _s;
  }

  class LngArray4_copyHelper {
  public:
    static inline LngArray4_slice* alloc() { return LngArray4_alloc(); }
    static inline LngArray4_slice* dup(const LngArray4_slice* p) { return LngArray4_dup(p); }
    static inline void free(LngArray4_slice* p) { LngArray4_free(p); }
  };

  typedef _CORBA_Array_Fix_Var<LngArray4_copyHelper,LngArray4_slice> LngArray4_var;
  typedef _CORBA_Array_Fix_Forany<LngArray4_copyHelper,LngArray4_slice> LngArray4_forany;

  typedef LngArray4_slice* LngArray4_out;

_CORBA_MODULE_END

#ifndef __protectPlugin__
#define __protectPlugin__

class protectPlugin;
class _objref_protectPlugin;
class _impl_protectPlugin;

typedef _objref_protectPlugin* protectPlugin_ptr;
typedef protectPlugin_ptr protectPluginRef;

class protectPlugin_Helper {
public:
  typedef protectPlugin_ptr _ptr_type;

  static _ptr_type _nil();
  static _CORBA_Boolean is_nil(_ptr_type);
  static void release(_ptr_type);
  static void duplicate(_ptr_type);
  static void marshalObjRef(_ptr_type, cdrStream&);
  static _ptr_type unmarshalObjRef(cdrStream&);
};

typedef _CORBA_ObjRef_Var<_objref_protectPlugin, protectPlugin_Helper> protectPlugin_var;
typedef _CORBA_ObjRef_OUT_arg<_objref_protectPlugin,protectPlugin_Helper > protectPlugin_out;

#endif

// interface protectPlugin
class protectPlugin {
public:
  // Declarations for this interface type.
  typedef protectPlugin_ptr _ptr_type;
  typedef protectPlugin_var _var_type;

  static _ptr_type _duplicate(_ptr_type);
  static _ptr_type _narrow(::CORBA::Object_ptr);
  static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
  
  static _ptr_type _nil();

  static inline void _marshalObjRef(_ptr_type, cdrStream&);

  static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
    omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
    if (o)
      return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
    else
      return _nil();
  }

  static _core_attr const char* _PD_repoId;

  // Other IDL defined within this scope.
  
};

class _objref_protectPlugin :
  public virtual OpenHRP::_objref_Plugin
{
public:
  void servoLock(const protectPluginTypes::LngArray4 inputID, protectPluginTypes::LngArray4 outputID);
  void servoUnLock(const protectPluginTypes::LngArray4 inputID, protectPluginTypes::LngArray4 outputID);
  ::CORBA::Boolean motionCancel(::CORBA::Octet& part);

  inline _objref_protectPlugin()  { _PR_setobj(0); }  // nil
  _objref_protectPlugin(omniIOR*, omniIdentity*);

protected:
  virtual ~_objref_protectPlugin();

  
private:
  virtual void* _ptrToObjRef(const char*);

  _objref_protectPlugin(const _objref_protectPlugin&);
  _objref_protectPlugin& operator = (const _objref_protectPlugin&);
  // not implemented

  friend class protectPlugin;
};

class _pof_protectPlugin : public _OMNI_NS(proxyObjectFactory) {
public:
  inline _pof_protectPlugin() : _OMNI_NS(proxyObjectFactory)(protectPlugin::_PD_repoId) {}
  virtual ~_pof_protectPlugin();

  virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
  virtual _CORBA_Boolean is_a(const char*) const;
};

class _impl_protectPlugin :
  public virtual OpenHRP::_impl_Plugin
{
public:
  virtual ~_impl_protectPlugin();

  virtual void servoLock(const protectPluginTypes::LngArray4 inputID, protectPluginTypes::LngArray4 outputID) = 0;
  virtual void servoUnLock(const protectPluginTypes::LngArray4 inputID, protectPluginTypes::LngArray4 outputID) = 0;
  virtual ::CORBA::Boolean motionCancel(::CORBA::Octet& part) = 0;
  
public:  // Really protected, workaround for xlC
  virtual _CORBA_Boolean _dispatch(omniCallHandle&);

private:
  virtual void* _ptrToInterface(const char*);
  virtual const char* _mostDerivedRepoId();
  
};




_CORBA_MODULE POA_protectPluginTypes
_CORBA_MODULE_BEG

_CORBA_MODULE_END

class POA_protectPlugin :
  public virtual _impl_protectPlugin,
  public virtual POA_OpenHRP::Plugin
{
public:
  virtual ~POA_protectPlugin();

  inline ::protectPlugin_ptr _this() {
    return (::protectPlugin_ptr) _do_this(::protectPlugin::_PD_repoId);
  }
};



_CORBA_MODULE OBV_protectPluginTypes
_CORBA_MODULE_BEG

_CORBA_MODULE_END



template <class _omniT>
class POA_protectPlugin_tie : public virtual POA_protectPlugin
{
public:
  POA_protectPlugin_tie(_omniT& t)
    : pd_obj(&t), pd_poa(0), pd_rel(0) {}
  POA_protectPlugin_tie(_omniT& t, ::PortableServer::POA_ptr p)
    : pd_obj(&t), pd_poa(p), pd_rel(0) {}
  POA_protectPlugin_tie(_omniT* t, _CORBA_Boolean r=1)
    : pd_obj(t), pd_poa(0), pd_rel(r) {}
  POA_protectPlugin_tie(_omniT* t, ::PortableServer::POA_ptr p,_CORBA_Boolean r=1)
    : pd_obj(t), pd_poa(p), pd_rel(r) {}
  ~POA_protectPlugin_tie() {
    if( pd_poa )  ::CORBA::release(pd_poa);
    if( pd_rel )  delete pd_obj;
  }

  _omniT* _tied_object() { return pd_obj; }

  void _tied_object(_omniT& t) {
    if( pd_rel )  delete pd_obj;
    pd_obj = &t;
    pd_rel = 0;
  }

  void _tied_object(_omniT* t, _CORBA_Boolean r=1) {
    if( pd_rel )  delete pd_obj;
    pd_obj = t;
    pd_rel = r;
  }

  _CORBA_Boolean _is_owner()        { return pd_rel; }
  void _is_owner(_CORBA_Boolean io) { pd_rel = io;   }

  ::PortableServer::POA_ptr _default_POA() {
    if( !pd_poa )  return ::PortableServer::POA::_the_root_poa();
    else           return ::PortableServer::POA::_duplicate(pd_poa);
  }

  void servoLock(const protectPluginTypes::LngArray4 inputID, protectPluginTypes::LngArray4 outputID) { pd_obj->servoLock(inputID, outputID); }
  void servoUnLock(const protectPluginTypes::LngArray4 inputID, protectPluginTypes::LngArray4 outputID) { pd_obj->servoUnLock(inputID, outputID); }
  ::CORBA::Boolean motionCancel(::CORBA::Octet& part) { return pd_obj->motionCancel(part); }
  void start() { pd_obj->start(); }
  void stop() { pd_obj->stop(); }
  void sendMsg(const char* msg) { pd_obj->sendMsg(msg); }


private:
  _omniT*                   pd_obj;
  ::PortableServer::POA_ptr pd_poa;
  _CORBA_Boolean            pd_rel;
};



#undef _core_attr
#undef _dyn_attr



inline void
protectPlugin::_marshalObjRef(::protectPlugin_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_protectPlugin
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_protectPlugin
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_protectPlugin
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_protectPlugin
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_protectPlugin
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_protectPlugin
#endif

#endif  // __protectPlugin_hh__

