# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.10
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.



from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_event_manager', [dirname(__file__)])
        except ImportError:
            import _event_manager
            return _event_manager
        if fp is not None:
            try:
                _mod = imp.load_module('_event_manager', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _event_manager = swig_import_helper()
    del swig_import_helper
else:
    import _event_manager
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0



def dateCreate(*args):
  return _event_manager.dateCreate(*args)
dateCreate = _event_manager.dateCreate

def dateDestroy(*args):
  return _event_manager.dateDestroy(*args)
dateDestroy = _event_manager.dateDestroy

def dateCopy(*args):
  return _event_manager.dateCopy(*args)
dateCopy = _event_manager.dateCopy

def dateGet(*args):
  return _event_manager.dateGet(*args)
dateGet = _event_manager.dateGet

def dateCompare(*args):
  return _event_manager.dateCompare(*args)
dateCompare = _event_manager.dateCompare

def dateTick(*args):
  return _event_manager.dateTick(*args)
dateTick = _event_manager.dateTick
EM_SUCCESS = _event_manager.EM_SUCCESS
EM_OUT_OF_MEMORY = _event_manager.EM_OUT_OF_MEMORY
EM_NULL_ARGUMENT = _event_manager.EM_NULL_ARGUMENT
EM_INVALID_DATE = _event_manager.EM_INVALID_DATE
EM_INVALID_EVENT_ID = _event_manager.EM_INVALID_EVENT_ID
EM_EVENT_ALREADY_EXISTS = _event_manager.EM_EVENT_ALREADY_EXISTS
EM_EVENT_ID_ALREADY_EXISTS = _event_manager.EM_EVENT_ID_ALREADY_EXISTS
EM_EVENT_NOT_EXISTS = _event_manager.EM_EVENT_NOT_EXISTS
EM_EVENT_ID_NOT_EXISTS = _event_manager.EM_EVENT_ID_NOT_EXISTS
EM_INVALID_MEMBER_ID = _event_manager.EM_INVALID_MEMBER_ID
EM_MEMBER_ID_ALREADY_EXISTS = _event_manager.EM_MEMBER_ID_ALREADY_EXISTS
EM_MEMBER_ID_NOT_EXISTS = _event_manager.EM_MEMBER_ID_NOT_EXISTS
EM_EVENT_AND_MEMBER_ALREADY_LINKED = _event_manager.EM_EVENT_AND_MEMBER_ALREADY_LINKED
EM_EVENT_AND_MEMBER_NOT_LINKED = _event_manager.EM_EVENT_AND_MEMBER_NOT_LINKED
EM_ERROR = _event_manager.EM_ERROR

def createEventManager(*args):
  return _event_manager.createEventManager(*args)
createEventManager = _event_manager.createEventManager

def destroyEventManager(*args):
  return _event_manager.destroyEventManager(*args)
destroyEventManager = _event_manager.destroyEventManager

def emAddEventByDate(*args):
  return _event_manager.emAddEventByDate(*args)
emAddEventByDate = _event_manager.emAddEventByDate

def emAddEventByDiff(*args):
  return _event_manager.emAddEventByDiff(*args)
emAddEventByDiff = _event_manager.emAddEventByDiff

def emRemoveEvent(*args):
  return _event_manager.emRemoveEvent(*args)
emRemoveEvent = _event_manager.emRemoveEvent

def emChangeEventDate(*args):
  return _event_manager.emChangeEventDate(*args)
emChangeEventDate = _event_manager.emChangeEventDate

def emAddMember(*args):
  return _event_manager.emAddMember(*args)
emAddMember = _event_manager.emAddMember

def emAddMemberToEvent(*args):
  return _event_manager.emAddMemberToEvent(*args)
emAddMemberToEvent = _event_manager.emAddMemberToEvent

def emRemoveMemberFromEvent(*args):
  return _event_manager.emRemoveMemberFromEvent(*args)
emRemoveMemberFromEvent = _event_manager.emRemoveMemberFromEvent

def emTick(*args):
  return _event_manager.emTick(*args)
emTick = _event_manager.emTick

def emGetEventsAmount(*args):
  return _event_manager.emGetEventsAmount(*args)
emGetEventsAmount = _event_manager.emGetEventsAmount

def emGetNextEvent(*args):
  return _event_manager.emGetNextEvent(*args)
emGetNextEvent = _event_manager.emGetNextEvent

def emPrintAllEvents(*args):
  return _event_manager.emPrintAllEvents(*args)
emPrintAllEvents = _event_manager.emPrintAllEvents

def emPrintAllResponsibleMembers(*args):
  return _event_manager.emPrintAllResponsibleMembers(*args)
emPrintAllResponsibleMembers = _event_manager.emPrintAllResponsibleMembers
# This file is compatible with both classic and new-style classes.


