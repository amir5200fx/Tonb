#pragma once
#ifndef _Cad_ApprxWireTraits_Header
#define _Cad_ApprxWireTraits_Header

namespace tnbLib
{

	// Forward Declarations [4/4/2022 Amir]

	template<class WireType>
	struct cad_apprx_wire_traits {};

	class GModel_ParaWire;
	class TModel_ParaWire;
	class GModel_ParaCurve;
	class TModel_ParaCurve;

	template<>
	struct cad_apprx_wire_traits<GModel_ParaWire> { typedef GModel_ParaCurve curveType; };

	template<>
	struct cad_apprx_wire_traits<TModel_ParaWire> { typedef TModel_ParaCurve curveType; };
}

#endif // !_Cad_ApprxWireTraits_Header
