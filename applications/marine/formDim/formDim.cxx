#include <HydStatic_Model.hxx>
#include <HydStatic_FormDim_Displacer.hxx>
#include <HydStatic_FormDim_Wetted.hxx>

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
	static const auto displacerCalculator = std::make_shared<formDim::Displacer>();
	static const auto wettedCalculator = std::make_shared<formDim::Wetted>();

	void loadModel(const std::string& name)
	{
		fileName fn(name);
		std::ifstream myFile(fn);

		boost::archive::polymorphic_text_iarchive ar(myFile);

		ar >> myModel;

		if (NOT myModel->FloatBody())
		{
			FatalErrorIn(FunctionSIG)
				<< "No floating body information has been detected" << endl
				<< abort(FatalError);
		}

		if (NOT myModel->StbModel())
		{
			FatalErrorIn(FunctionSIG)
				<< "No Stability Model has been detected" << endl
				<< abort(FatalError);
		}
	}

	void calcDisplacer()
	{
		const auto& displacer = myModel->StbModel()->Hull();
		const auto& body = displacer->Body();
		
		displacerCalculator->LoadBody(body);
		displacerCalculator->Perform();
	}

	void calcWetted()
	{
		const auto& wettedBody = myModel->FloatBody()->Wetted();
		
		wettedCalculator->LoadBody(wettedBody);
		wettedCalculator->Perform();
	}

}