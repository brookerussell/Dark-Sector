// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME DarkSector_MediatorVisibleDecayDict

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
#include "MediatorDecay.h"
#include "MediatorDetectorIntercept.h"
#include "MediatorProduction.h"
#include "MediatorSelection.h"
#include "NeutralMesonProduction.h"
#include "SanityPlots.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *NeutralMesonProduction_Dictionary();
   static void NeutralMesonProduction_TClassManip(TClass*);
   static void *new_NeutralMesonProduction(void *p = 0);
   static void *newArray_NeutralMesonProduction(Long_t size, void *p);
   static void delete_NeutralMesonProduction(void *p);
   static void deleteArray_NeutralMesonProduction(void *p);
   static void destruct_NeutralMesonProduction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::NeutralMesonProduction*)
   {
      ::NeutralMesonProduction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::NeutralMesonProduction));
      static ::ROOT::TGenericClassInfo 
         instance("NeutralMesonProduction", "NeutralMesonProduction.h", 31,
                  typeid(::NeutralMesonProduction), DefineBehavior(ptr, ptr),
                  &NeutralMesonProduction_Dictionary, isa_proxy, 4,
                  sizeof(::NeutralMesonProduction) );
      instance.SetNew(&new_NeutralMesonProduction);
      instance.SetNewArray(&newArray_NeutralMesonProduction);
      instance.SetDelete(&delete_NeutralMesonProduction);
      instance.SetDeleteArray(&deleteArray_NeutralMesonProduction);
      instance.SetDestructor(&destruct_NeutralMesonProduction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::NeutralMesonProduction*)
   {
      return GenerateInitInstanceLocal((::NeutralMesonProduction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::NeutralMesonProduction*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *NeutralMesonProduction_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::NeutralMesonProduction*)0x0)->GetClass();
      NeutralMesonProduction_TClassManip(theClass);
   return theClass;
   }

   static void NeutralMesonProduction_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *SanityPlots_Dictionary();
   static void SanityPlots_TClassManip(TClass*);
   static void *new_SanityPlots(void *p = 0);
   static void *newArray_SanityPlots(Long_t size, void *p);
   static void delete_SanityPlots(void *p);
   static void deleteArray_SanityPlots(void *p);
   static void destruct_SanityPlots(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SanityPlots*)
   {
      ::SanityPlots *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::SanityPlots));
      static ::ROOT::TGenericClassInfo 
         instance("SanityPlots", "SanityPlots.h", 30,
                  typeid(::SanityPlots), DefineBehavior(ptr, ptr),
                  &SanityPlots_Dictionary, isa_proxy, 4,
                  sizeof(::SanityPlots) );
      instance.SetNew(&new_SanityPlots);
      instance.SetNewArray(&newArray_SanityPlots);
      instance.SetDelete(&delete_SanityPlots);
      instance.SetDeleteArray(&deleteArray_SanityPlots);
      instance.SetDestructor(&destruct_SanityPlots);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SanityPlots*)
   {
      return GenerateInitInstanceLocal((::SanityPlots*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::SanityPlots*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *SanityPlots_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::SanityPlots*)0x0)->GetClass();
      SanityPlots_TClassManip(theClass);
   return theClass;
   }

   static void SanityPlots_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MediatorProduction_Dictionary();
   static void MediatorProduction_TClassManip(TClass*);
   static void *new_MediatorProduction(void *p = 0);
   static void *newArray_MediatorProduction(Long_t size, void *p);
   static void delete_MediatorProduction(void *p);
   static void deleteArray_MediatorProduction(void *p);
   static void destruct_MediatorProduction(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MediatorProduction*)
   {
      ::MediatorProduction *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MediatorProduction));
      static ::ROOT::TGenericClassInfo 
         instance("MediatorProduction", "MediatorProduction.h", 34,
                  typeid(::MediatorProduction), DefineBehavior(ptr, ptr),
                  &MediatorProduction_Dictionary, isa_proxy, 4,
                  sizeof(::MediatorProduction) );
      instance.SetNew(&new_MediatorProduction);
      instance.SetNewArray(&newArray_MediatorProduction);
      instance.SetDelete(&delete_MediatorProduction);
      instance.SetDeleteArray(&deleteArray_MediatorProduction);
      instance.SetDestructor(&destruct_MediatorProduction);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MediatorProduction*)
   {
      return GenerateInitInstanceLocal((::MediatorProduction*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MediatorProduction*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MediatorProduction_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MediatorProduction*)0x0)->GetClass();
      MediatorProduction_TClassManip(theClass);
   return theClass;
   }

   static void MediatorProduction_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MediatorSelection_Dictionary();
   static void MediatorSelection_TClassManip(TClass*);
   static void *new_MediatorSelection(void *p = 0);
   static void *newArray_MediatorSelection(Long_t size, void *p);
   static void delete_MediatorSelection(void *p);
   static void deleteArray_MediatorSelection(void *p);
   static void destruct_MediatorSelection(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MediatorSelection*)
   {
      ::MediatorSelection *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MediatorSelection));
      static ::ROOT::TGenericClassInfo 
         instance("MediatorSelection", "MediatorSelection.h", 34,
                  typeid(::MediatorSelection), DefineBehavior(ptr, ptr),
                  &MediatorSelection_Dictionary, isa_proxy, 4,
                  sizeof(::MediatorSelection) );
      instance.SetNew(&new_MediatorSelection);
      instance.SetNewArray(&newArray_MediatorSelection);
      instance.SetDelete(&delete_MediatorSelection);
      instance.SetDeleteArray(&deleteArray_MediatorSelection);
      instance.SetDestructor(&destruct_MediatorSelection);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MediatorSelection*)
   {
      return GenerateInitInstanceLocal((::MediatorSelection*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MediatorSelection*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MediatorSelection_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MediatorSelection*)0x0)->GetClass();
      MediatorSelection_TClassManip(theClass);
   return theClass;
   }

   static void MediatorSelection_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MediatorDetectorIntercept_Dictionary();
   static void MediatorDetectorIntercept_TClassManip(TClass*);
   static void *new_MediatorDetectorIntercept(void *p = 0);
   static void *newArray_MediatorDetectorIntercept(Long_t size, void *p);
   static void delete_MediatorDetectorIntercept(void *p);
   static void deleteArray_MediatorDetectorIntercept(void *p);
   static void destruct_MediatorDetectorIntercept(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MediatorDetectorIntercept*)
   {
      ::MediatorDetectorIntercept *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MediatorDetectorIntercept));
      static ::ROOT::TGenericClassInfo 
         instance("MediatorDetectorIntercept", "MediatorDetectorIntercept.h", 31,
                  typeid(::MediatorDetectorIntercept), DefineBehavior(ptr, ptr),
                  &MediatorDetectorIntercept_Dictionary, isa_proxy, 4,
                  sizeof(::MediatorDetectorIntercept) );
      instance.SetNew(&new_MediatorDetectorIntercept);
      instance.SetNewArray(&newArray_MediatorDetectorIntercept);
      instance.SetDelete(&delete_MediatorDetectorIntercept);
      instance.SetDeleteArray(&deleteArray_MediatorDetectorIntercept);
      instance.SetDestructor(&destruct_MediatorDetectorIntercept);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MediatorDetectorIntercept*)
   {
      return GenerateInitInstanceLocal((::MediatorDetectorIntercept*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MediatorDetectorIntercept*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MediatorDetectorIntercept_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MediatorDetectorIntercept*)0x0)->GetClass();
      MediatorDetectorIntercept_TClassManip(theClass);
   return theClass;
   }

   static void MediatorDetectorIntercept_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MediatorDecay_Dictionary();
   static void MediatorDecay_TClassManip(TClass*);
   static void *new_MediatorDecay(void *p = 0);
   static void *newArray_MediatorDecay(Long_t size, void *p);
   static void delete_MediatorDecay(void *p);
   static void deleteArray_MediatorDecay(void *p);
   static void destruct_MediatorDecay(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MediatorDecay*)
   {
      ::MediatorDecay *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MediatorDecay));
      static ::ROOT::TGenericClassInfo 
         instance("MediatorDecay", "MediatorDecay.h", 33,
                  typeid(::MediatorDecay), DefineBehavior(ptr, ptr),
                  &MediatorDecay_Dictionary, isa_proxy, 4,
                  sizeof(::MediatorDecay) );
      instance.SetNew(&new_MediatorDecay);
      instance.SetNewArray(&newArray_MediatorDecay);
      instance.SetDelete(&delete_MediatorDecay);
      instance.SetDeleteArray(&deleteArray_MediatorDecay);
      instance.SetDestructor(&destruct_MediatorDecay);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MediatorDecay*)
   {
      return GenerateInitInstanceLocal((::MediatorDecay*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MediatorDecay*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MediatorDecay_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MediatorDecay*)0x0)->GetClass();
      MediatorDecay_TClassManip(theClass);
   return theClass;
   }

   static void MediatorDecay_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_NeutralMesonProduction(void *p) {
      return  p ? new(p) ::NeutralMesonProduction : new ::NeutralMesonProduction;
   }
   static void *newArray_NeutralMesonProduction(Long_t nElements, void *p) {
      return p ? new(p) ::NeutralMesonProduction[nElements] : new ::NeutralMesonProduction[nElements];
   }
   // Wrapper around operator delete
   static void delete_NeutralMesonProduction(void *p) {
      delete ((::NeutralMesonProduction*)p);
   }
   static void deleteArray_NeutralMesonProduction(void *p) {
      delete [] ((::NeutralMesonProduction*)p);
   }
   static void destruct_NeutralMesonProduction(void *p) {
      typedef ::NeutralMesonProduction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::NeutralMesonProduction

namespace ROOT {
   // Wrappers around operator new
   static void *new_SanityPlots(void *p) {
      return  p ? new(p) ::SanityPlots : new ::SanityPlots;
   }
   static void *newArray_SanityPlots(Long_t nElements, void *p) {
      return p ? new(p) ::SanityPlots[nElements] : new ::SanityPlots[nElements];
   }
   // Wrapper around operator delete
   static void delete_SanityPlots(void *p) {
      delete ((::SanityPlots*)p);
   }
   static void deleteArray_SanityPlots(void *p) {
      delete [] ((::SanityPlots*)p);
   }
   static void destruct_SanityPlots(void *p) {
      typedef ::SanityPlots current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::SanityPlots

namespace ROOT {
   // Wrappers around operator new
   static void *new_MediatorProduction(void *p) {
      return  p ? new(p) ::MediatorProduction : new ::MediatorProduction;
   }
   static void *newArray_MediatorProduction(Long_t nElements, void *p) {
      return p ? new(p) ::MediatorProduction[nElements] : new ::MediatorProduction[nElements];
   }
   // Wrapper around operator delete
   static void delete_MediatorProduction(void *p) {
      delete ((::MediatorProduction*)p);
   }
   static void deleteArray_MediatorProduction(void *p) {
      delete [] ((::MediatorProduction*)p);
   }
   static void destruct_MediatorProduction(void *p) {
      typedef ::MediatorProduction current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MediatorProduction

namespace ROOT {
   // Wrappers around operator new
   static void *new_MediatorSelection(void *p) {
      return  p ? new(p) ::MediatorSelection : new ::MediatorSelection;
   }
   static void *newArray_MediatorSelection(Long_t nElements, void *p) {
      return p ? new(p) ::MediatorSelection[nElements] : new ::MediatorSelection[nElements];
   }
   // Wrapper around operator delete
   static void delete_MediatorSelection(void *p) {
      delete ((::MediatorSelection*)p);
   }
   static void deleteArray_MediatorSelection(void *p) {
      delete [] ((::MediatorSelection*)p);
   }
   static void destruct_MediatorSelection(void *p) {
      typedef ::MediatorSelection current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MediatorSelection

namespace ROOT {
   // Wrappers around operator new
   static void *new_MediatorDetectorIntercept(void *p) {
      return  p ? new(p) ::MediatorDetectorIntercept : new ::MediatorDetectorIntercept;
   }
   static void *newArray_MediatorDetectorIntercept(Long_t nElements, void *p) {
      return p ? new(p) ::MediatorDetectorIntercept[nElements] : new ::MediatorDetectorIntercept[nElements];
   }
   // Wrapper around operator delete
   static void delete_MediatorDetectorIntercept(void *p) {
      delete ((::MediatorDetectorIntercept*)p);
   }
   static void deleteArray_MediatorDetectorIntercept(void *p) {
      delete [] ((::MediatorDetectorIntercept*)p);
   }
   static void destruct_MediatorDetectorIntercept(void *p) {
      typedef ::MediatorDetectorIntercept current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MediatorDetectorIntercept

namespace ROOT {
   // Wrappers around operator new
   static void *new_MediatorDecay(void *p) {
      return  p ? new(p) ::MediatorDecay : new ::MediatorDecay;
   }
   static void *newArray_MediatorDecay(Long_t nElements, void *p) {
      return p ? new(p) ::MediatorDecay[nElements] : new ::MediatorDecay[nElements];
   }
   // Wrapper around operator delete
   static void delete_MediatorDecay(void *p) {
      delete ((::MediatorDecay*)p);
   }
   static void deleteArray_MediatorDecay(void *p) {
      delete [] ((::MediatorDecay*)p);
   }
   static void destruct_MediatorDecay(void *p) {
      typedef ::MediatorDecay current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MediatorDecay

namespace {
  void TriggerDictionaryInitialization_libDarkSector_MediatorVisibleDecay_Impl() {
    static const char* headers[] = {
"MediatorDecay.h",
"MediatorDetectorIntercept.h",
"MediatorProduction.h",
"MediatorSelection.h",
"NeutralMesonProduction.h",
"SanityPlots.h",
0
    };
    static const char* includePaths[] = {
"/Users/br/BasicSoftware/root-6.04.12/include",
"/Users/br/BasicSoftware/larlite/UserDev/DarkSector/MediatorVisibleDecay/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$NeutralMesonProduction.h")))  NeutralMesonProduction;
class __attribute__((annotate("$clingAutoload$SanityPlots.h")))  SanityPlots;
class __attribute__((annotate("$clingAutoload$MediatorProduction.h")))  MediatorProduction;
class __attribute__((annotate("$clingAutoload$MediatorSelection.h")))  MediatorSelection;
class __attribute__((annotate("$clingAutoload$MediatorDetectorIntercept.h")))  MediatorDetectorIntercept;
class __attribute__((annotate("$clingAutoload$MediatorDecay.h")))  MediatorDecay;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MediatorDecay.h"
#include "MediatorDetectorIntercept.h"
#include "MediatorProduction.h"
#include "MediatorSelection.h"
#include "NeutralMesonProduction.h"
#include "SanityPlots.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MediatorDecay", payloadCode, "@",
"MediatorDetectorIntercept", payloadCode, "@",
"MediatorProduction", payloadCode, "@",
"MediatorSelection", payloadCode, "@",
"NeutralMesonProduction", payloadCode, "@",
"SanityPlots", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libDarkSector_MediatorVisibleDecay",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libDarkSector_MediatorVisibleDecay_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libDarkSector_MediatorVisibleDecay_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libDarkSector_MediatorVisibleDecay() {
  TriggerDictionaryInitialization_libDarkSector_MediatorVisibleDecay_Impl();
}
