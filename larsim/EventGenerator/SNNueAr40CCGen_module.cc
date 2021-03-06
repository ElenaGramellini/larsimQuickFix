////////////////////////////////////////////////////////////////////////////////
/// \file  SNNueAr40CCGen_module.cc
/// \brief Supernova Nue-Ar CC interaction generator
/// 
/// Module that produces MC particles from supernova electron neutrinos
/// interacting via charge current with Ar40
/// 
/// \author  gleb.sinev@duke.edu
////////////////////////////////////////////////////////////////////////////////
#ifndef EVGEN_SNNUEARCCGEN
#define EVGEN_SNNUEARCCGEN

// Framework includes
#include "art/Framework/Core/EDProducer.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Principal/Run.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "art/Framework/Services/Optional/RandomNumberGenerator.h"
#include "fhiclcpp/ParameterSet.h"

// art extensions
#include "nutools/RandomUtils/NuRandomService.h"

// nutools includes
#include "nusimdata/SimulationBase/MCTruth.h"

// LArSoft includes
#include "larcoreobj/SummaryData/RunData.h"
#include "larcore/Geometry/Geometry.h"

#include "CLHEP/Random/RandomEngine.h"

// C++ includes
#include <map>

#include "NueAr40CCGenerator.h"

namespace evgen {
  
  /// Module producing electrons and gammas from supernova neutrino 
  /// interactions with liquid argon (based on SingleGen)
  class SNNueAr40CCGen : public art::EDProducer {

    public:

      explicit SNNueAr40CCGen(fhicl::ParameterSet const& pset);

      void beginRun(art::Run& run) override;

      void produce(art::Event& event) override;

    private:

    evgen::NueAr40CCGenerator fGenerator;

  };

}

namespace evgen {

  //____________________________________________________________________________
  SNNueAr40CCGen::SNNueAr40CCGen(fhicl::ParameterSet const& pset)
    : EDProducer{pset}
    , fGenerator(evgen::NueAr40CCGenerator
                             (pset.get< fhicl::ParameterSet >("GeneratorAlg")))
  {

    produces< std::vector< simb::MCTruth > >();
    produces< sumdata::RunData, art::InRun >();

    // Create a default random engine: obtain the random seed
    // freom NuRandomService, unless overriden in configuration with key "Seed"
    (void)art::ServiceHandle< rndm::NuRandomService >()
      ->createEngine(*this, pset, "Seed");

  }

  //____________________________________________________________________________
  void SNNueAr40CCGen::beginRun(art::Run& run)
  {

    // Store information about the geometry we are using in run information
    art::ServiceHandle< geo::Geometry > geo;
    std::unique_ptr< sumdata::RunData > 
      runCol(new sumdata::RunData(geo->DetectorName()));

    run.put(std::move(runCol));

    return;

  }

  //____________________________________________________________________________
  void SNNueAr40CCGen::produce(art::Event& event)
  {

    std::unique_ptr< std::vector< simb::MCTruth > > 
                                truthCol(new std::vector< simb::MCTruth >);

    // Get an engine from the random number generator
    art::ServiceHandle< art::RandomNumberGenerator > randomNumberGenerator;
    CLHEP::HepRandomEngine &engine = randomNumberGenerator->getEngine(art::ScheduleID::first(),
                                                                      moduleDescription().moduleLabel());

    std::vector<simb::MCTruth> truths = fGenerator.Generate(engine);

    for(unsigned int i = 0; i < truths.size(); ++i) {
      truthCol->emplace_back(truths[i]);
    }

    event.put(std::move(truthCol));

    return;

  }

}

namespace evgen {

  DEFINE_ART_MODULE(SNNueAr40CCGen)

}

#endif
////////////////////////////////////////////////////////////////////////////////
