#include <Marine_Bodies.hxx>
#include <Marine_Models.hxx>
#include <Marine_TankModeler.hxx>
#include <Marine_SailModeler.hxx>
#include <Marine_DisplacerModeler.hxx>
#include <StbGMaker_Model.hxx>

#include <TnbError.hxx>
#include <OSstream.hxx>

#include <vector>

#include <boost/archive/polymorphic_binary_iarchive.hpp>
#include <boost/archive/polymorphic_binary_oarchive.hpp>

#include <boost/archive/polymorphic_text_iarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>

namespace tnbLib
{
	typedef std::shared_ptr<Marine_Model> model_t;

	static model_t myHull;
	static std::vector<model_t> mySails;
	static std::vector<model_t> myTanks;

	static size_t nbSails = 0;
	static size_t nbTanks = 0;

	static const std::string hullFolder = "hull";
	static const std::string sailsFolder = "sails";
	static const std::string tanksFolder = "tanks";

	static bool hullTag = false;
	static bool sailTag = false;
	static bool tankTag = false;

	static std::shared_ptr<StbGMaker_Model> myModel;

	void loadHull(const std::string& name)
	{
		std::string address = ".\\" + hullFolder + "\\" + name;
		std::fstream file;
		file.open(address, ios::in);

		if (file.fail())
		{
			FatalErrorIn(FunctionSIG)
				<< "file was not found" << endl
				<< abort(FatalError);
		}

		boost::archive::polymorphic_text_iarchive oa(file);

		oa >> myHull;

		if (!myHull)
		{
			FatalErrorIn(FunctionSIG)
				<< "no hull has been loaded" << endl
				<< abort(FatalError);
		}

		hullTag = true;
	}

	void loadSails(const std::string& name)
	{
		mySails.reserve(nbSails);
		for (size_t i = 0; i < nbSails; i++)
		{
			std::string address = ".\\" + sailsFolder + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			boost::archive::polymorphic_text_iarchive oa(file);

			model_t sail;

			oa >> sail;

			mySails.push_back(sail);
		}

		sailTag = true;
	}

	void loadTanks(const std::string& name)
	{
		myTanks.reserve(nbTanks);
		for (size_t i = 0; i < nbTanks; i++)
		{
			std::string address = ".\\" + tanksFolder + "\\" + name;
			std::fstream file;
			file.open(address, ios::in);

			if (file.fail())
			{
				FatalErrorIn(FunctionSIG)
					<< "file was not found" << endl
					<< abort(FatalError);
			}

			boost::archive::polymorphic_text_iarchive oa(file);

			model_t tank;

			oa >> tank;

			myTanks.push_back(tank);
		}

		tankTag = true;
	}

	
}
