#include <NumAlg_GA.hxx>

const std::string tnbLib::NumAlg_GA_Base::GA_Info::extension = ".gaInfo";

Standard_Real tnbLib::NumAlg_GA_Base::GA_Info::DEFAULT_MUTATION(0.15);
Standard_Real tnbLib::NumAlg_GA_Base::GA_Info::DEFAULT_SELECTION(0.5);

Standard_Integer tnbLib::NumAlg_GA_Base::GA_Info::MAX_NB_GENERATIONS(100);
Standard_Integer tnbLib::NumAlg_GA_Base::GA_Info::POP_SIZE(50);
Standard_Integer tnbLib::NumAlg_GA_Base::GA_Info::NB_PARAMETERS(0);

unsigned short tnbLib::NumAlg_GA_Base::verbose(0);