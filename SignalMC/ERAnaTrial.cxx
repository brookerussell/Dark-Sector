#ifndef ERTOOL_ERANATRIAL_CXX
#define ERTOOL_ERANATRIAL_CXX

#include "ERAnaTrial.h"

namespace ertool {

  ERAnaTrial::ERAnaTrial(const std::string& name) : AnaBase(name)
  {}

  void ERAnaTrial::Reset()
  {}

  void ERAnaTrial::AcceptPSet(const ::fcllite::PSet& cfg)
  {}

  void ERAnaTrial::ProcessBegin()
  {}

  bool ERAnaTrial::Analyze(const EventData &data, const ParticleGraph &ps)
  { return true; }

  void ERAnaTrial::ProcessEnd(TFile* fout)
  {}

}

#endif
