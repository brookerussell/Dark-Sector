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
#include "ERAnaTrial.h"
#include "LeptophobicMC.h"
#include "Meson.h"
#include "VB.h"
#include "test.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *test_Dictionary();
   static void test_TClassManip(TClass*);
   static void *new_test(void *p = 0);
   static void *newArray_test(Long_t size, void *p);
   static void delete_test(void *p);
   static void deleteArray_test(void *p);
   static void destruct_test(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::test*)
   {
      ::test *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::test));
      static ::ROOT::TGenericClassInfo 
         instance("test", "test.h", 23,
                  typeid(::test), DefineBehavior(ptr, ptr),
                  &test_Dictionary, isa_proxy, 4,
                  sizeof(::test) );
      instance.SetNew(&new_test);
      instance.SetNewArray(&newArray_test);
      instance.SetDelete(&delete_test);
      instance.SetDeleteArray(&deleteArray_test);
      instance.SetDestructor(&destruct_test);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::test*)
   {
      return GenerateInitInstanceLocal((::test*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::test*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *test_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::test*)0x0)->GetClass();
      test_TClassManip(theClass);
   return theClass;
   }

   static void test_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *ertoolcLcLERAnaTrial_Dictionary();
   static void ertoolcLcLERAnaTrial_TClassManip(TClass*);
   static void *new_ertoolcLcLERAnaTrial(void *p = 0);
   static void *newArray_ertoolcLcLERAnaTrial(Long_t size, void *p);
   static void delete_ertoolcLcLERAnaTrial(void *p);
   static void deleteArray_ertoolcLcLERAnaTrial(void *p);
   static void destruct_ertoolcLcLERAnaTrial(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ertool::ERAnaTrial*)
   {
      ::ertool::ERAnaTrial *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::ertool::ERAnaTrial));
      static ::ROOT::TGenericClassInfo 
         instance("ertool::ERAnaTrial", "ERAnaTrial.h", 26,
                  typeid(::ertool::ERAnaTrial), DefineBehavior(ptr, ptr),
                  &ertoolcLcLERAnaTrial_Dictionary, isa_proxy, 4,
                  sizeof(::ertool::ERAnaTrial) );
      instance.SetNew(&new_ertoolcLcLERAnaTrial);
      instance.SetNewArray(&newArray_ertoolcLcLERAnaTrial);
      instance.SetDelete(&delete_ertoolcLcLERAnaTrial);
      instance.SetDeleteArray(&deleteArray_ertoolcLcLERAnaTrial);
      instance.SetDestructor(&destruct_ertoolcLcLERAnaTrial);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ertool::ERAnaTrial*)
   {
      return GenerateInitInstanceLocal((::ertool::ERAnaTrial*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::ertool::ERAnaTrial*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *ertoolcLcLERAnaTrial_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::ertool::ERAnaTrial*)0x0)->GetClass();
      ertoolcLcLERAnaTrial_TClassManip(theClass);
   return theClass;
   }

   static void ertoolcLcLERAnaTrial_TClassManip(TClass* ){
   }

} // end of namespace ROOT

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
   // Wrappers around operator new
   static void *new_test(void *p) {
      return  p ? new(p) ::test : new ::test;
   }
   static void *newArray_test(Long_t nElements, void *p) {
      return p ? new(p) ::test[nElements] : new ::test[nElements];
   }
   // Wrapper around operator delete
   static void delete_test(void *p) {
      delete ((::test*)p);
   }
   static void deleteArray_test(void *p) {
      delete [] ((::test*)p);
   }
   static void destruct_test(void *p) {
      typedef ::test current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::test

namespace ROOT {
   // Wrappers around operator new
   static void *new_ertoolcLcLERAnaTrial(void *p) {
      return  p ? ::new((::ROOT::TOperatorNewHelper*)p) ::ertool::ERAnaTrial : new ::ertool::ERAnaTrial;
   }
   static void *newArray_ertoolcLcLERAnaTrial(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::TOperatorNewHelper*)p) ::ertool::ERAnaTrial[nElements] : new ::ertool::ERAnaTrial[nElements];
   }
   // Wrapper around operator delete
   static void delete_ertoolcLcLERAnaTrial(void *p) {
      delete ((::ertool::ERAnaTrial*)p);
   }
   static void deleteArray_ertoolcLcLERAnaTrial(void *p) {
      delete [] ((::ertool::ERAnaTrial*)p);
   }
   static void destruct_ertoolcLcLERAnaTrial(void *p) {
      typedef ::ertool::ERAnaTrial current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ertool::ERAnaTrial

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

namespace {
  void TriggerDictionaryInitialization_libDarkSector_SignalMC_Impl() {
    static const char* headers[] = {
"Decay.h",
"ERAnaTrial.h",
"LeptophobicMC.h",
"Meson.h",
"VB.h",
"test.h",
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
class __attribute__((annotate("$clingAutoload$test.h")))  test;
namespace ertool{class __attribute__((annotate("$clingAutoload$ERAnaTrial.h")))  ERAnaTrial;}
class __attribute__((annotate("$clingAutoload$LeptophobicMC.h")))  LeptophobicMC;
class __attribute__((annotate("$clingAutoload$Meson.h")))  Meson;
class __attribute__((annotate("$clingAutoload$VB.h")))  VB;
class __attribute__((annotate("$clingAutoload$Decay.h")))  Decay;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "Decay.h"
#include "ERAnaTrial.h"
#include "LeptophobicMC.h"
#include "Meson.h"
#include "VB.h"
#include "test.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Decay", payloadCode, "@",
"LeptophobicMC", payloadCode, "@",
"Meson", payloadCode, "@",
"VB", payloadCode, "@",
"ertool::ERAnaTrial", payloadCode, "@",
"test", payloadCode, "@",
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
