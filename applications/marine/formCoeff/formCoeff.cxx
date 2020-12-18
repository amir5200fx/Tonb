#include <HydStatic_Model.hxx>
#include <HydStatic_FormCoeff.hxx>

#include <HydStatic_FloatBody.hxx>
#include <StbGMaker_Model.hxx>
#include <Marine_Models.hxx>
#include <Marine_Bodies.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<HydStatic_Model> hModel_t;

	static hModel_t myModel;
	static std::shared_ptr<formCoeff::Wetted> formCoeffCalculator;

	void loadModdel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myModel;
		if (NOT myModel->FloatBody())
		{
			FatalErrorIn(FunctionSIG)
				<< "NNo floating body information has been detected" << endl
				<< abort(FatalError);
		}
	}

	void calcFormCoeff()
	{
		const auto& wettedBody = myModel->FloatBody()->Wetted();
		formCoeffCalculator = std::make_shared<formCoeff::Wetted>(wettedBody);
		formCoeffCalculator->Perform();
	}
}