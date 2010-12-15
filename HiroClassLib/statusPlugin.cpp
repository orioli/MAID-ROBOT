// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.

#include "statusPlugin.hpp"
#include <omniORB4/IOP_S.h>
#include <omniORB4/IOP_C.h>
#include <omniORB4/callDescriptor.h>
#include <omniORB4/callHandle.h>
#include <omniORB4/objTracker.h>


OMNI_USING_NAMESPACE(omni)

static const char* _0RL_library_version = omniORB_4_1;



_init_in_def_( const ::CORBA::Octet statusPluginTypes::PART_CHEST = 1; )

_init_in_def_( const ::CORBA::Octet statusPluginTypes::PART_NECK = 2; )

_init_in_def_( const ::CORBA::Octet statusPluginTypes::PART_RARM = 4; )

_init_in_def_( const ::CORBA::Octet statusPluginTypes::PART_LARM = 8; )

_init_in_def_( const ::CORBA::Octet statusPluginTypes::PART_ALL = 15; )

_init_in_def_( const ::CORBA::ULongLong statusPluginTypes::JOINT_CHEST = _CORBA_LONGLONG_CONST(1U); )

_init_in_def_( const ::CORBA::ULongLong statusPluginTypes::JOINT_NECK = _CORBA_LONGLONG_CONST(6U); )

_init_in_def_( const ::CORBA::ULongLong statusPluginTypes::JOINT_RARM = _CORBA_LONGLONG_CONST(504U); )

_init_in_def_( const ::CORBA::ULongLong statusPluginTypes::JOINT_LARM = _CORBA_LONGLONG_CONST(32256U); )

_init_in_def_( const ::CORBA::ULongLong statusPluginTypes::JOINT_ALL = _CORBA_LONGLONG_CONST(32767U); )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_CHEST = 0; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_NECK = 1; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_RARM = 2; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_LARM = 3; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_PART = 7; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_ANGLE = 0; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_EULER = 8; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_QUATER = 16; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_MATRIX = 24; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_EXPRESS = 56; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_COMMAND = 0; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_STATUS = 64; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_COM_STAT = 192; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_MM_DEG = 0; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_M_RAD = 256; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_DIMENSION = 768; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_LIM_UP = 1024; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_LIM_DOWN = 2048; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_LIM_ACC = 3072; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_LIM_VEL = 4096; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_LIM_DEC = 5120; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_MC_WRITE = 15360; )

_init_in_def_( const ::CORBA::UShort statusPluginTypes::K_VALUE_TYPE = 15360; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::SYSTEM_ON = 1U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::CALIB_YET = 16U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::CALIB_DONE = 32U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::SERVO_ON = 256U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::SERVO_OFF = 512U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::EMERGENCY_CLEAR = 4096U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::SERVO_EMERGENCY = 8192U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::SERVO_READY = 65536U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::EMER_OR_BUTTON = 131072U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::EMER_AND_BUTTON = 262144U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::PROTECT_RELEASE = 1048576U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::PROTECT_STOP = 2097152U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::PROTECT_PARTS = 4194304U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::MOTOR_NORMAL = 16777216U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::MOTOR_HEATUP = 33554432U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::FAN_MOVE = 268435456U; )

_init_in_def_( const ::CORBA::ULong statusPluginTypes::FAN_STOP = 536870912U; )

statusPlugin_ptr statusPlugin_Helper::_nil() {
  return ::statusPlugin::_nil();
}

::CORBA::Boolean statusPlugin_Helper::is_nil(::statusPlugin_ptr p) {
  return ::CORBA::is_nil(p);

}

void statusPlugin_Helper::release(::statusPlugin_ptr p) {
  ::CORBA::release(p);
}

void statusPlugin_Helper::marshalObjRef(::statusPlugin_ptr obj, cdrStream& s) {
  ::statusPlugin::_marshalObjRef(obj, s);
}

statusPlugin_ptr statusPlugin_Helper::unmarshalObjRef(cdrStream& s) {
  return ::statusPlugin::_unmarshalObjRef(s);
}

void statusPlugin_Helper::duplicate(::statusPlugin_ptr obj) {
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
}

statusPlugin_ptr
statusPlugin::_duplicate(::statusPlugin_ptr obj)
{
  if( obj && !obj->_NP_is_nil() )  omni::duplicateObjRef(obj);
  return obj;
}

statusPlugin_ptr
statusPlugin::_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_realNarrow(_PD_repoId);
  return e ? e : _nil();
}


statusPlugin_ptr
statusPlugin::_unchecked_narrow(::CORBA::Object_ptr obj)
{
  if( !obj || obj->_NP_is_nil() || obj->_NP_is_pseudo() ) return _nil();
  _ptr_type e = (_ptr_type) obj->_PR_getobj()->_uncheckedNarrow(_PD_repoId);
  return e ? e : _nil();
}

statusPlugin_ptr
statusPlugin::_nil()
{
#ifdef OMNI_UNLOADABLE_STUBS
  static _objref_statusPlugin _the_nil_obj;
  return &_the_nil_obj;
#else
  static _objref_statusPlugin* _the_nil_ptr = 0;
  if( !_the_nil_ptr ) {
    omni::nilRefLock().lock();
    if( !_the_nil_ptr ) {
      _the_nil_ptr = new _objref_statusPlugin;
      registerNilCorbaObject(_the_nil_ptr);
    }
    omni::nilRefLock().unlock();
  }
  return _the_nil_ptr;
#endif
}

const char* statusPlugin::_PD_repoId = "IDL:statusPlugin:1.0";


typedef OpenHRP::Plugin OpenHRP_Plugin;
typedef OpenHRP::_impl_Plugin OpenHRP__impl_Plugin;
typedef OpenHRP::_objref_Plugin OpenHRP__objref_Plugin;

typedef OpenHRP::CommandReceiver OpenHRP_CommandReceiver;
typedef OpenHRP::_impl_CommandReceiver OpenHRP__impl_CommandReceiver;
typedef OpenHRP::_objref_CommandReceiver OpenHRP__objref_CommandReceiver;

_objref_statusPlugin::~_objref_statusPlugin() {
  
}


_objref_statusPlugin::_objref_statusPlugin(omniIOR* ior, omniIdentity* id) :
   omniObjRef(::statusPlugin::_PD_repoId, ior, id, 1),
   OpenHRP__objref_Plugin(ior, id)
   
{
  _PR_setobj(this);
}

void*
_objref_statusPlugin::_ptrToObjRef(const char* id)
{
  if( id == ::statusPlugin::_PD_repoId )
    return (::statusPlugin_ptr) this;
  if( id == ::OpenHRP::Plugin::_PD_repoId )
    return (::OpenHRP::Plugin_ptr) this;

  if( id == ::OpenHRP::CommandReceiver::_PD_repoId )
    return (::OpenHRP::CommandReceiver_ptr) this;


  if( id == ::CORBA::Object::_PD_repoId )
    return (::CORBA::Object_ptr) this;

  if( omni::strMatch(id, ::statusPlugin::_PD_repoId) )
    return (::statusPlugin_ptr) this;
  if( omni::strMatch(id, ::OpenHRP::Plugin::_PD_repoId) )
    return (::OpenHRP::Plugin_ptr) this;

  if( omni::strMatch(id, ::OpenHRP::CommandReceiver::_PD_repoId) )
    return (::OpenHRP::CommandReceiver_ptr) this;


  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (::CORBA::Object_ptr) this;

  return 0;
}

// Proxy call descriptor class. Mangled signature:
//  _cboolean_n_cunsigned_plonglong_i_cboolean_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_00000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_00000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  statusPluginTypes::jointType arg_0_;
  statusPluginTypes::jointType* arg_0;
  ::CORBA::Boolean arg_1;
  hiroCommonStatus::statSequence_var arg_2;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_00000000::marshalArguments(cdrStream& _n)
{
  *arg_0 >>= _n;
  _n.marshalBoolean(arg_1);

}

void _0RL_cd_2E300CB9E99AAF41_00000000::unmarshalArguments(cdrStream& _n)
{
  (statusPluginTypes::jointType&)arg_0_ <<= _n;
  arg_0 = &arg_0_;
  arg_1 = _n.unmarshalBoolean();

}

void _0RL_cd_2E300CB9E99AAF41_00000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  *arg_0 >>= _n;
  (const hiroCommonStatus::statSequence&) arg_2 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_00000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  (statusPluginTypes::jointType&)*arg_0 <<= _n;
  arg_2 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_2 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_10000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_00000000* tcd = (_0RL_cd_2E300CB9E99AAF41_00000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->inMotionJoint(*tcd->arg_0, tcd->arg_1, tcd->arg_2.out());


}

::CORBA::Boolean _objref_statusPlugin::inMotionJoint(statusPluginTypes::jointType& joint, ::CORBA::Boolean wait, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_00000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_10000000, "inMotionJoint", 14);
  _call_desc.arg_0 = &(statusPluginTypes::jointType&) joint;
  _call_desc.arg_1 = wait;

  _invoke(_call_desc);
  status = _call_desc.arg_2._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_n_coctet_i_cboolean_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_20000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_20000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  statusPluginTypes::partType arg_0_;
  statusPluginTypes::partType* arg_0;
  ::CORBA::Boolean arg_1;
  hiroCommonStatus::statSequence_var arg_2;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_20000000::marshalArguments(cdrStream& _n)
{
  _n.marshalOctet(*arg_0);
  _n.marshalBoolean(arg_1);

}

void _0RL_cd_2E300CB9E99AAF41_20000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = _n.unmarshalOctet();
  arg_0 = &arg_0_;
  arg_1 = _n.unmarshalBoolean();

}

void _0RL_cd_2E300CB9E99AAF41_20000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  _n.marshalOctet(*arg_0);
  (const hiroCommonStatus::statSequence&) arg_2 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_20000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  *arg_0 = _n.unmarshalOctet();
  arg_2 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_2 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_30000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_20000000* tcd = (_0RL_cd_2E300CB9E99AAF41_20000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->inMotionPart(*tcd->arg_0, tcd->arg_1, tcd->arg_2.out());


}

::CORBA::Boolean _objref_statusPlugin::inMotionPart(statusPluginTypes::partType& part, ::CORBA::Boolean wait, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_20000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_30000000, "inMotionPart", 13);
  _call_desc.arg_0 = &(statusPluginTypes::partType&) part;
  _call_desc.arg_1 = wait;

  _invoke(_call_desc);
  status = _call_desc.arg_2._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_coctet_i_coctet_i_cunsigned_pshort_o_cstatusPluginTypes_mJointValues_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_40000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_40000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  ::CORBA::Octet arg_0;
  ::CORBA::Octet arg_1;
  statusPluginTypes::kindType arg_2;
  statusPluginTypes::JointValues_var arg_3;
  hiroCommonStatus::statSequence_var arg_4;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_40000000::marshalArguments(cdrStream& _n)
{
  _n.marshalOctet(arg_0);
  _n.marshalOctet(arg_1);
  arg_2 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_40000000::unmarshalArguments(cdrStream& _n)
{
  arg_0 = _n.unmarshalOctet();
  arg_1 = _n.unmarshalOctet();
  (statusPluginTypes::kindType&)arg_2 <<= _n;

}

void _0RL_cd_2E300CB9E99AAF41_40000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  (const statusPluginTypes::JointValues&) arg_3 >>= _n;
  (const hiroCommonStatus::statSequence&) arg_4 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_40000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  arg_3 = new statusPluginTypes::JointValues;
  (statusPluginTypes::JointValues&)arg_3 <<= _n;
  arg_4 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_4 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_50000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_40000000* tcd = (_0RL_cd_2E300CB9E99AAF41_40000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->getJointValue(tcd->arg_0, tcd->arg_1, tcd->arg_2, tcd->arg_3.out(), tcd->arg_4.out());


}

::CORBA::Boolean _objref_statusPlugin::getJointValue(::CORBA::Octet startJoint, ::CORBA::Octet jointNum, statusPluginTypes::kindType outKind, statusPluginTypes::JointValues_out joint_values, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_40000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_50000000, "getJointValue", 14);
  _call_desc.arg_0 = startJoint;
  _call_desc.arg_1 = jointNum;
  _call_desc.arg_2 = outKind;

  _invoke(_call_desc);
  joint_values = _call_desc.arg_3._retn();
  status = _call_desc.arg_4._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_cunsigned_pshort_o_cstatusPluginTypes_mJointValues_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_60000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_60000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  statusPluginTypes::kindType arg_0;
  statusPluginTypes::JointValues_var arg_1;
  hiroCommonStatus::statSequence_var arg_2;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_60000000::marshalArguments(cdrStream& _n)
{
  arg_0 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_60000000::unmarshalArguments(cdrStream& _n)
{
  (statusPluginTypes::kindType&)arg_0 <<= _n;

}

void _0RL_cd_2E300CB9E99AAF41_60000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  (const statusPluginTypes::JointValues&) arg_1 >>= _n;
  (const hiroCommonStatus::statSequence&) arg_2 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_60000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  arg_1 = new statusPluginTypes::JointValues;
  (statusPluginTypes::JointValues&)arg_1 <<= _n;
  arg_2 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_2 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_70000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_60000000* tcd = (_0RL_cd_2E300CB9E99AAF41_60000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->getPositionArm(tcd->arg_0, tcd->arg_1.out(), tcd->arg_2.out());


}

::CORBA::Boolean _objref_statusPlugin::getPositionArm(statusPluginTypes::kindType outKind, statusPluginTypes::JointValues_out joint_values, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_60000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_70000000, "getPositionArm", 15);
  _call_desc.arg_0 = outKind;

  _invoke(_call_desc);
  joint_values = _call_desc.arg_1._retn();
  status = _call_desc.arg_2._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_coctet_o_cdouble_o_cstring_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_80000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_80000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  ::CORBA::Octet arg_0;
  ::CORBA::Double arg_1;
  ::CORBA::String_var arg_2;
  hiroCommonStatus::statSequence_var arg_3;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_80000000::marshalArguments(cdrStream& _n)
{
  _n.marshalOctet(arg_0);

}

void _0RL_cd_2E300CB9E99AAF41_80000000::unmarshalArguments(cdrStream& _n)
{
  arg_0 = _n.unmarshalOctet();

}

void _0RL_cd_2E300CB9E99AAF41_80000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  arg_1 >>= _n;
  _n.marshalString(arg_2,0);
  (const hiroCommonStatus::statSequence&) arg_3 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_80000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  (::CORBA::Double&)arg_1 <<= _n;
  arg_2 = _n.unmarshalString(0);
  arg_3 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_3 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_90000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_80000000* tcd = (_0RL_cd_2E300CB9E99AAF41_80000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->getChangeMcName(tcd->arg_0, tcd->arg_1, tcd->arg_2.out(), tcd->arg_3.out());


}

::CORBA::Boolean _objref_statusPlugin::getChangeMcName(::CORBA::Octet jointNum, ::CORBA::Double& mcID, ::CORBA::String_out name, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_80000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_90000000, "getChangeMcName", 16);
  _call_desc.arg_0 = jointNum;

  _invoke(_call_desc);
  mcID = _call_desc.arg_1;
  name = _call_desc.arg_2._retn();
  status = _call_desc.arg_3._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_cstatusPluginTypes_mJointValues_i_cstatusPluginTypes_mJointValues_i_cunsigned_pshort_i_cunsigned_pshort_o_cstatusPluginTypes_mJointValues_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_a0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_a0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  statusPluginTypes::JointValues_var arg_0_;
  const statusPluginTypes::JointValues* arg_0;
  statusPluginTypes::JointValues_var arg_1_;
  const statusPluginTypes::JointValues* arg_1;
  statusPluginTypes::kindType arg_2;
  statusPluginTypes::kindType arg_3;
  statusPluginTypes::JointValues_var arg_4;
  hiroCommonStatus::statSequence_var arg_5;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_a0000000::marshalArguments(cdrStream& _n)
{
  (const statusPluginTypes::JointValues&) *arg_0 >>= _n;
  (const statusPluginTypes::JointValues&) *arg_1 >>= _n;
  arg_2 >>= _n;
  arg_3 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_a0000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = new statusPluginTypes::JointValues;
  (statusPluginTypes::JointValues&)arg_0_ <<= _n;
  arg_0 = &arg_0_.in();
  arg_1_ = new statusPluginTypes::JointValues;
  (statusPluginTypes::JointValues&)arg_1_ <<= _n;
  arg_1 = &arg_1_.in();
  (statusPluginTypes::kindType&)arg_2 <<= _n;
  (statusPluginTypes::kindType&)arg_3 <<= _n;

}

void _0RL_cd_2E300CB9E99AAF41_a0000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  (const statusPluginTypes::JointValues&) arg_4 >>= _n;
  (const hiroCommonStatus::statSequence&) arg_5 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_a0000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  arg_4 = new statusPluginTypes::JointValues;
  (statusPluginTypes::JointValues&)arg_4 <<= _n;
  arg_5 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_5 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_b0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_a0000000* tcd = (_0RL_cd_2E300CB9E99AAF41_a0000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->convertData(*tcd->arg_0, *tcd->arg_1, tcd->arg_2, tcd->arg_3, tcd->arg_4.out(), tcd->arg_5.out());


}

::CORBA::Boolean _objref_statusPlugin::convertData(const statusPluginTypes::JointValues& inValues, const statusPluginTypes::JointValues& handOffset, statusPluginTypes::kindType inKind, statusPluginTypes::kindType outKind, statusPluginTypes::JointValues_out outValues, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_a0000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_b0000000, "convertData", 12);
  _call_desc.arg_0 = &(statusPluginTypes::JointValues&) inValues;
  _call_desc.arg_1 = &(statusPluginTypes::JointValues&) handOffset;
  _call_desc.arg_2 = inKind;
  _call_desc.arg_3 = outKind;

  _invoke(_call_desc);
  outValues = _call_desc.arg_4._retn();
  status = _call_desc.arg_5._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  _cboolean_i_cstatusPluginTypes_mJointValues_i_cunsigned_pshort_o_chiroCommonStatus_mstatSequence
class _0RL_cd_2E300CB9E99AAF41_c0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_c0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  void marshalArguments(cdrStream&);
  void unmarshalArguments(cdrStream&);

  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  statusPluginTypes::JointValues_var arg_0_;
  const statusPluginTypes::JointValues* arg_0;
  statusPluginTypes::kindType arg_1;
  hiroCommonStatus::statSequence_var arg_2;
  ::CORBA::Boolean result;
};

void _0RL_cd_2E300CB9E99AAF41_c0000000::marshalArguments(cdrStream& _n)
{
  (const statusPluginTypes::JointValues&) *arg_0 >>= _n;
  arg_1 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_c0000000::unmarshalArguments(cdrStream& _n)
{
  arg_0_ = new statusPluginTypes::JointValues;
  (statusPluginTypes::JointValues&)arg_0_ <<= _n;
  arg_0 = &arg_0_.in();
  (statusPluginTypes::kindType&)arg_1 <<= _n;

}

void _0RL_cd_2E300CB9E99AAF41_c0000000::marshalReturnedValues(cdrStream& _n)
{
  _n.marshalBoolean(result);
  (const hiroCommonStatus::statSequence&) arg_2 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_c0000000::unmarshalReturnedValues(cdrStream& _n)
{
  result = _n.unmarshalBoolean();
  arg_2 = new hiroCommonStatus::statSequence;
  (hiroCommonStatus::statSequence&)arg_2 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_d0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_c0000000* tcd = (_0RL_cd_2E300CB9E99AAF41_c0000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->setHandOffset(*tcd->arg_0, tcd->arg_1, tcd->arg_2.out());


}

::CORBA::Boolean _objref_statusPlugin::setHandOffset(const statusPluginTypes::JointValues& handOffset, statusPluginTypes::kindType inKind, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_c0000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_d0000000, "setHandOffset", 14);
  _call_desc.arg_0 = &(statusPluginTypes::JointValues&) handOffset;
  _call_desc.arg_1 = inKind;

  _invoke(_call_desc);
  status = _call_desc.arg_2._retn();
  return _call_desc.result;


}
// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_e0000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_60000000* tcd = (_0RL_cd_2E300CB9E99AAF41_60000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  tcd->result = impl->getHandOffset(tcd->arg_0, tcd->arg_1.out(), tcd->arg_2.out());


}

::CORBA::Boolean _objref_statusPlugin::getHandOffset(statusPluginTypes::kindType outKind, statusPluginTypes::JointValues_out handOffset, hiroCommonStatus::statSequence_out status)
{
  _0RL_cd_2E300CB9E99AAF41_60000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_e0000000, "getHandOffset", 14);
  _call_desc.arg_0 = outKind;

  _invoke(_call_desc);
  handOffset = _call_desc.arg_1._retn();
  status = _call_desc.arg_2._retn();
  return _call_desc.result;


}
// Proxy call descriptor class. Mangled signature:
//  void_o_cstatusPluginTypes_mRobotStatus
class _0RL_cd_2E300CB9E99AAF41_f0000000
  : public omniCallDescriptor
{
public:
  inline _0RL_cd_2E300CB9E99AAF41_f0000000(LocalCallFn lcfn,const char* op_,size_t oplen,_CORBA_Boolean upcall=0):
     omniCallDescriptor(lcfn, op_, oplen, 0, 0, 0, upcall)
  {
    
  }
  
  
  void unmarshalReturnedValues(cdrStream&);
  void marshalReturnedValues(cdrStream&);
  
  
  statusPluginTypes::RobotStatus_var arg_0;
};

void _0RL_cd_2E300CB9E99AAF41_f0000000::marshalReturnedValues(cdrStream& _n)
{
  (const statusPluginTypes::RobotStatus&) arg_0 >>= _n;

}

void _0RL_cd_2E300CB9E99AAF41_f0000000::unmarshalReturnedValues(cdrStream& _n)
{
  arg_0 = new statusPluginTypes::RobotStatus;
  (statusPluginTypes::RobotStatus&)arg_0 <<= _n;

}

// Local call call-back function.
static void
_0RL_lcfn_2E300CB9E99AAF41_01000000(omniCallDescriptor* cd, omniServant* svnt)
{
  _0RL_cd_2E300CB9E99AAF41_f0000000* tcd = (_0RL_cd_2E300CB9E99AAF41_f0000000*)cd;
  _impl_statusPlugin* impl = (_impl_statusPlugin*) svnt->_ptrToInterface(statusPlugin::_PD_repoId);
  impl->getStatus(tcd->arg_0.out());


}

void _objref_statusPlugin::getStatus(statusPluginTypes::RobotStatus_out robotStatuses)
{
  _0RL_cd_2E300CB9E99AAF41_f0000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_01000000, "getStatus", 10);


  _invoke(_call_desc);
  robotStatuses = _call_desc.arg_0._retn();


}
_pof_statusPlugin::~_pof_statusPlugin() {}


omniObjRef*
_pof_statusPlugin::newObjRef(omniIOR* ior, omniIdentity* id)
{
  return new ::_objref_statusPlugin(ior, id);
}


::CORBA::Boolean
_pof_statusPlugin::is_a(const char* id) const
{
  if( omni::ptrStrMatch(id, ::statusPlugin::_PD_repoId) )
    return 1;
  if( omni::ptrStrMatch(id, OpenHRP::Plugin::_PD_repoId) )
    return 1;

  if( omni::ptrStrMatch(id, OpenHRP::CommandReceiver::_PD_repoId) )
    return 1;


  return 0;
}

const _pof_statusPlugin _the_pof_statusPlugin;

_impl_statusPlugin::~_impl_statusPlugin() {}


::CORBA::Boolean
_impl_statusPlugin::_dispatch(omniCallHandle& _handle)
{
  const char* op = _handle.operation_name();

  if( omni::strMatch(op, "inMotionJoint") ) {

    _0RL_cd_2E300CB9E99AAF41_00000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_10000000, "inMotionJoint", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "inMotionPart") ) {

    _0RL_cd_2E300CB9E99AAF41_20000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_30000000, "inMotionPart", 13, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getJointValue") ) {

    _0RL_cd_2E300CB9E99AAF41_40000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_50000000, "getJointValue", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getPositionArm") ) {

    _0RL_cd_2E300CB9E99AAF41_60000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_70000000, "getPositionArm", 15, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getChangeMcName") ) {

    _0RL_cd_2E300CB9E99AAF41_80000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_90000000, "getChangeMcName", 16, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "convertData") ) {

    _0RL_cd_2E300CB9E99AAF41_a0000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_b0000000, "convertData", 12, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "setHandOffset") ) {

    _0RL_cd_2E300CB9E99AAF41_c0000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_d0000000, "setHandOffset", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getHandOffset") ) {

    _0RL_cd_2E300CB9E99AAF41_60000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_e0000000, "getHandOffset", 14, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  if( omni::strMatch(op, "getStatus") ) {

    _0RL_cd_2E300CB9E99AAF41_f0000000 _call_desc(_0RL_lcfn_2E300CB9E99AAF41_01000000, "getStatus", 10, 1);
    
    _handle.upcall(this,_call_desc);
    return 1;
  }

  
#ifndef _MSC_VER
  if( OpenHRP__impl_Plugin::_dispatch(_handle) ) {
    return 1;
  }
#else
  // Work-around for incorrect MSVC code generation.
  if( ((OpenHRP__impl_Plugin*)this)->
      OpenHRP__impl_Plugin::_dispatch(_handle) ) {
    return 1;
  }
#endif


  return 0;
}

void*
_impl_statusPlugin::_ptrToInterface(const char* id)
{
  if( id == ::statusPlugin::_PD_repoId )
    return (::_impl_statusPlugin*) this;
  if( id == ::OpenHRP::Plugin::_PD_repoId )
    return (::OpenHRP::_impl_Plugin*) this;

  if( id == ::OpenHRP::CommandReceiver::_PD_repoId )
    return (::OpenHRP::_impl_CommandReceiver*) this;


  if( id == ::CORBA::Object::_PD_repoId )
    return (void*) 1;

  if( omni::strMatch(id, ::statusPlugin::_PD_repoId) )
    return (::_impl_statusPlugin*) this;
  if( omni::strMatch(id, ::OpenHRP::Plugin::_PD_repoId) )
    return (::OpenHRP::_impl_Plugin*) this;

  if( omni::strMatch(id, ::OpenHRP::CommandReceiver::_PD_repoId) )
    return (::OpenHRP::_impl_CommandReceiver*) this;


  if( omni::strMatch(id, ::CORBA::Object::_PD_repoId) )
    return (void*) 1;
  return 0;
}

const char*
_impl_statusPlugin::_mostDerivedRepoId()
{
  return ::statusPlugin::_PD_repoId;
}

POA_statusPlugin::~POA_statusPlugin() {}

