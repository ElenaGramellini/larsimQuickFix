
# for c2: the problem is in fhiclcpp/types/detail/Sequence.icc
cet_add_compiler_flags( CXX -Wno-missing-braces )

#include_directories ( $ENV{MARLEY_INC} )

art_make(
      LIB_LIBRARIES
                        larsim_Simulation
                        lardataobj_Simulation
                        lardataobj_Simulation_dict
                        nusimdata_SimulationBase
	                larcorealg_Geometry
                        larcore_Geometry_Geometry_service
                        nutools_RandomUtils_NuRandomService_service
                        ${MARLEY}
                        ${MARLEY_ROOT}
                        ${ART_FRAMEWORK_CORE}
                        ${ART_FRAMEWORK_PRINCIPAL}
                        ${ART_FRAMEWORK_SERVICES_REGISTRY}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
                        ${MF_MESSAGELOGGER}
                        
                        ${FHICLCPP}
                        cetlib cetlib_except
                        ${ROOT_BASIC_LIB_LIST}
                        ${ROOT_GEOM}
      MODULE_LIBRARIES 
                        larsim_EventGenerator_MARLEY
                        larsim_Simulation
                        lardata_Utilities
                        lardataobj_Simulation
                        lardataobj_Simulation_dict
                        nusimdata_SimulationBase
                        larcoreobj_SummaryData
                        larcorealg_Geometry
                        larcore_Geometry_Geometry_service
                        nutools_RandomUtils_NuRandomService_service
                        ${MARLEY}
                        ${MARLEY_ROOT}
                        ${ART_FRAMEWORK_CORE}
                        ${ART_FRAMEWORK_PRINCIPAL}
                        ${ART_FRAMEWORK_SERVICES_REGISTRY}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL_TFILESERVICE_SERVICE}
                        ${ART_FRAMEWORK_SERVICES_OPTIONAL_RANDOMNUMBERGENERATOR_SERVICE}
                        art_Persistency_Common
                        art_Persistency_Provenance
                        art_Utilities
                        canvas
                        ${MF_MESSAGELOGGER}
                        
                        ${FHICLCPP}
                        cetlib cetlib_except
                        ${CLHEP}
                        ${ROOT_BASIC_LIB_LIST}
                        ${ROOT_GEOM}
                        ${G4_LIB_LIST}
        )

install_headers()
install_fhicl()
install_source()
