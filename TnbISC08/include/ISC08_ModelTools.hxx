#pragma once
#ifndef _ISC08_ModelTools_Header
#define _ISC08_ModelTools_Header

#include <ISC08_Module.hxx>
#include <ISC08_Model.hxx>
#include <ISC08_SolutionData_PassengerFwd.hxx>

namespace tnbLib
{

	// Forward Declarations
	

	class ISC08_ModelTools
	{

	public:

		static ISC08_Model::VesselParams RetrieveVesselParameters(const std::shared_ptr<isc08Lib::SolutionData_Passenger>& theSolu);

		static ISC08_Model::Props RetrieveProperties(const std::shared_ptr<isc08Lib::SolutionData_Passenger>& theSolu);


	};
}

#endif // !_ISC08_ModelTools_Header
