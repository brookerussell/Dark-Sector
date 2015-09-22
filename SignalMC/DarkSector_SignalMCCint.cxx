// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DarkSector_SignalMCCint

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "Decay.h"
#include "LeptophobicMC.h"
#include "Meson.h"
#include "ProductionCheck.h"
#include "VB.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *LeptophobicMC_Dictionary();
   static void LeptophobicMC_TClassManip(TClass*);
   static void *new_LeptophobicMC(void *p = 0);
   static void *newArray_LeptophobicMC(Long_t size, void *p);
   static void delete_LeptophobicMC(void *p);
   static void deleteArray_LeptophobicMC(void *p);
   static void destruct_LeptophobicMC(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::LeptophobicMC*)
   {
      ::LeptophobicMC *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::LeptophobicMC));
      static ::ROOT::TGenericClassInfo 
         instance("LeptophobicMC", "LeptophobicMC.h", 29,
                  typeid(::LeptophobicMC), DefineBehavior(ptr, ptr),
                  &LeptophobicMC_Dictionary, isa_proxy, 4,
                  sizeof(::LeptophobicMC) );
      instance.SetNew(&new_LeptophobicMC);
      instance.SetNewArray(&newArray_LeptophobicMC);
      instance.SetDelete(&delete_LeptophobicMC);
      instance.SetDeleteArray(&deleteArray_LeptophobicMC);
      instance.SetDestructor(&destruct_LeptophobicMC);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::LeptophobicMC*)
   {
      return GenerateInitInstanceLocal((::LeptophobicMC*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::LeptophobicMC*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *LeptophobicMC_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::LeptophobicMC*)0x0)->GetClass();
      LeptophobicMC_TClassManip(theClass);
   return theClass;
   }

   static void LeptophobicMC_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Meson_Dictionary();
   static void Meson_TClassManip(TClass*);
   static void *new_Meson(void *p = 0);
   static void *newArray_Meson(Long_t size, void *p);
   static void delete_Meson(void *p);
   static void deleteArray_Meson(void *p);
   static void destruct_Meson(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Meson*)
   {
      ::Meson *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Meson));
      static ::ROOT::TGenericClassInfo 
         instance("Meson", "Meson.h", 30,
                  typeid(::Meson), DefineBehavior(ptr, ptr),
                  &Meson_Dictionary, isa_proxy, 4,
                  sizeof(::Meson) );
      instance.SetNew(&new_Meson);
      instance.SetNewArray(&newArray_Meson);
      instance.SetDelete(&delete_Meson);
      instance.SetDeleteArray(&deleteArray_Meson);
      instance.SetDestructor(&destruct_Meson);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Meson*)
   {
      return GenerateInitInstanceLocal((::Meson*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Meson*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Meson_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Meson*)0x0)->GetClass();
      Meson_TClassManip(theClass);
   return theClass;
   }

   static void Meson_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *VB_Dictionary();
   static void VB_TClassManip(TClass*);
   static void *new_VB(void *p = 0);
   static void *newArray_VB(Long_t size, void *p);
   static void delete_VB(void *p);
   static void deleteArray_VB(void *p);
   static void destruct_VB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::VB*)
   {
      ::VB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::VB));
      static ::ROOT::TGenericClassInfo 
         instance("VB", "VB.h", 32,
                  typeid(::VB), DefineBehavior(ptr, ptr),
                  &VB_Dictionary, isa_proxy, 4,
                  sizeof(::VB) );
      instance.SetNew(&new_VB);
      instance.SetNewArray(&newArray_VB);
      instance.SetDelete(&delete_VB);
      instance.SetDeleteArray(&deleteArray_VB);
      instance.SetDestructor(&destruct_VB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::VB*)
   {
      return GenerateInitInstanceLocal((::VB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::VB*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *VB_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::VB*)0x0)->GetClass();
      VB_TClassManip(theClass);
   return theClass;
   }

   static void VB_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *Decay_Dictionary();
   static void Decay_TClassManip(TClass*);
   static void *new_Decay(void *p = 0);
   static void *newArray_Decay(Long_t size, void *p);
   static void delete_Decay(void *p);
   static void deleteArray_Decay(void *p);
   static void destruct_Decay(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Decay*)
   {
      ::Decay *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::Decay));
      static ::ROOT::TGenericClassInfo 
         instance("Decay", "Decay.h", 32,
                  typeid(::Decay), DefineBehavior(ptr, ptr),
                  &Decay_Dictionary, isa_proxy, 4,
                  sizeof(::Decay) );
      instance.SetNew(&new_Decay);
      instance.SetNewArray(&newArray_Decay);
      instance.SetDelete(&delete_Decay);
      instance.SetDeleteArray(&deleteArray_Decay);
      instance.SetDestructor(&destruct_Decay);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Decay*)
   {
      return GenerateInitInstanceLocal((::Decay*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Decay*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *Decay_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::Decay*)0x0)->GetClass();
      Decay_TClassManip(theClass);
   return theClass;
   }

   static void Decay_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ProductionCheck_Dictionary();
   static void ProductionCheck_TClassManip(TClass*);
   static void *new_ProductionCheck(void *p = 0);
   static void *newArray_ProductionCheck(Long_t size, void *p);
   static void delete_ProductionCheck(void *p);
   static void deleteArray_ProductionCheck(void *p);
   static void destruct_ProductionCheck(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ProductionCheck*)
   {
      ::ProductionCheck *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ProductionCheck));
      static ::ROOT::TGenericClassInfo 
         instance("ProductionCheck", "ProductionCheck.h", 30,
                  typeid(::ProductionCheck), DefineBehavior(ptr, ptr),
                  &ProductionCheck_Dictionary, isa_proxy, 4,
                  sizeof(::ProductionCheck) );
      instance.SetNew(&new_ProductionCheck);
      instance.SetNewArray(&newArray_ProductionCheck);
      instance.SetDelete(&delete_ProductionCheck);
      instance.SetDeleteArray(&deleteArray_ProductionCheck);
      instance.SetDestructor(&destruct_ProductionCheck);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ProductionCheck*)
   {
      return GenerateInitInstanceLocal((::ProductionCheck*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ProductionCheck*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ProductionCheck_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ProductionCheck*)0x0)->GetClass();
      ProductionCheck_TClassManip(theClass);
   return theClass;
   }

   static void ProductionCheck_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_LeptophobicMC(void *p) {
      return  p ? new(p) ::LeptophobicMC : new ::LeptophobicMC;
   }
   static void *newArray_LeptophobicMC(Long_t nElements, void *p) {
      return p ? new(p) ::LeptophobicMC[nElements] : new ::LeptophobicMC[nElements];
   }
   // Wrapper around operator delete
   static void delete_LeptophobicMC(void *p) {
      delete ((::LeptophobicMC*)p);
   }
   static void deleteArray_LeptophobicMC(void *p) {
      delete [] ((::LeptophobicMC*)p);
   }
   static void destruct_LeptophobicMC(void *p) {
      typedef ::LeptophobicMC current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::LeptophobicMC

namespace ROOT {
   // Wrappers around operator new
   static void *new_Meson(void *p) {
      return  p ? new(p) ::Meson : new ::Meson;
   }
   static void *newArray_Meson(Long_t nElements, void *p) {
      return p ? new(p) ::Meson[nElements] : new ::Meson[nElements];
   }
   // Wrapper around operator delete
   static void delete_Meson(void *p) {
      delete ((::Meson*)p);
   }
   static void deleteArray_Meson(void *p) {
      delete [] ((::Meson*)p);
   }
   static void destruct_Meson(void *p) {
      typedef ::Meson current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Meson

namespace ROOT {
   // Wrappers around operator new
   static void *new_VB(void *p) {
      return  p ? new(p) ::VB : new ::VB;
   }
   static void *newArray_VB(Long_t nElements, void *p) {
      return p ? new(p) ::VB[nElements] : new ::VB[nElements];
   }
   // Wrapper around operator delete
   static void delete_VB(void *p) {
      delete ((::VB*)p);
   }
   static void deleteArray_VB(void *p) {
      delete [] ((::VB*)p);
   }
   static void destruct_VB(void *p) {
      typedef ::VB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::VB

namespace ROOT {
   // Wrappers around operator new
   static void *new_Decay(void *p) {
      return  p ? new(p) ::Decay : new ::Decay;
   }
   static void *newArray_Decay(Long_t nElements, void *p) {
      return p ? new(p) ::Decay[nElements] : new ::Decay[nElements];
   }
   // Wrapper around operator delete
   static void delete_Decay(void *p) {
      delete ((::Decay*)p);
   }
   static void deleteArray_Decay(void *p) {
      delete [] ((::Decay*)p);
   }
   static void destruct_Decay(void *p) {
      typedef ::Decay current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Decay

namespace ROOT {
   // Wrappers around operator new
   static void *new_ProductionCheck(void *p) {
      return  p ? new(p) ::ProductionCheck : new ::ProductionCheck;
   }
   static void *newArray_ProductionCheck(Long_t nElements, void *p) {
      return p ? new(p) ::ProductionCheck[nElements] : new ::ProductionCheck[nElements];
   }
   // Wrapper around operator delete
   static void delete_ProductionCheck(void *p) {
      delete ((::ProductionCheck*)p);
   }
   static void deleteArray_ProductionCheck(void *p) {
      delete [] ((::ProductionCheck*)p);
   }
   static void destruct_ProductionCheck(void *p) {
      typedef ::ProductionCheck current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ProductionCheck

namespace {
  void TriggerDictionaryInitialization_libDarkSector_SignalMC_Impl() {
    static const char* headers[] = {
"Decay.h",
"LeptophobicMC.h",
"Meson.h",
"ProductionCheck.h",
"VB.h",
0
    };
    static const char* includePaths[] = {
"/Users/ber9/BasicSoftware/MyLArLite/UserDev/BasicTool",
"/Users/ber9/BasicSoftware/MyLArLite/UserDev/SelectionTool",
"/Users/ber9/BasicSoftware/root/include",
"/Users/ber9/BasicSoftware/MyLArLite/UserDev/DarkSector/SignalMC/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$LeptophobicMC.h")))  LeptophobicMC;
class __attribute__((annotate("$clingAutoload$Meson.h")))  Meson;
class __attribute__((annotate("$clingAutoload$VB.h")))  VB;
class __attribute__((annotate("$clingAutoload$Decay.h")))  Decay;
class __attribute__((annotate("$clingAutoload$ProductionCheck.h")))  ProductionCheck;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "Decay.h"
#include "LeptophobicMC.h"
#include "Meson.h"
#include "ProductionCheck.h"
#include "VB.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Decay", payloadCode, "@",
"LeptophobicMC", payloadCode, "@",
"Meson", payloadCode, "@",
"ProductionCheck", payloadCode, "@",
"VB", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libDarkSector_SignalMC",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libDarkSector_SignalMC_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libDarkSector_SignalMC_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libDarkSector_SignalMC() {
  TriggerDictionaryInitialization_libDarkSector_SignalMC_Impl();
}
