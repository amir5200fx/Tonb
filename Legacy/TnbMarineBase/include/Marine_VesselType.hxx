#pragma once
#ifndef _Marine_VesselType_Header
#define _Marine_VesselType_Header

namespace tnbLib
{

	enum class Marine_VesselType
	{

		cargo,
		cargo_carrying_timer_deck_cargoes,
		passanger,
		fishing,
		special_purpose,
		offshore_supply,
		mobile_offshore_drilling_units,
		pontoons,
		cargo_carrying_containers_on_deck_and_containerships
	};
}

#endif // !_Marine_VesselType_Header
