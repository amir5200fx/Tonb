#include <calculatedFvsPatchVectorNFields.hxx>

#include <fvsPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

#define doMakeFvsPatchTypeField(type, Type, args)                          \
    makeFvsPatchTypeField(fvsPatch##Type##Field, calculatedFvsPatch##Type##Field);

	template <>
	const ::tnbLib::word calculatedFvsPatchVector2Field::typeName(calculatedFvsPatchVector2Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchVector2Field::debug(
		std::string(calculatedFvsPatchVector2Field::typeName_()), 0, "");;
	fvsPatchVector2Field::addpatchConstructorToTable<calculatedFvsPatchVector2Field>
	addcalculatedFvsPatchVector2FieldpatchConstructorTofvsPatchVector2FieldTable_;
	fvsPatchVector2Field::addpatchMapperConstructorToTable<calculatedFvsPatchVector2Field>
	addcalculatedFvsPatchVector2FieldpatchMapperConstructorTofvsPatchVector2FieldTable_;
	fvsPatchVector2Field::adddictionaryConstructorToTable<calculatedFvsPatchVector2Field>
	addcalculatedFvsPatchVector2FielddictionaryConstructorTofvsPatchVector2FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchVector3Field::typeName(calculatedFvsPatchVector3Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchVector3Field::debug(
		std::string(calculatedFvsPatchVector3Field::typeName_()), 0, "");;
	fvsPatchVector3Field::addpatchConstructorToTable<calculatedFvsPatchVector3Field>
	addcalculatedFvsPatchVector3FieldpatchConstructorTofvsPatchVector3FieldTable_;
	fvsPatchVector3Field::addpatchMapperConstructorToTable<calculatedFvsPatchVector3Field>
	addcalculatedFvsPatchVector3FieldpatchMapperConstructorTofvsPatchVector3FieldTable_;
	fvsPatchVector3Field::adddictionaryConstructorToTable<calculatedFvsPatchVector3Field>
	addcalculatedFvsPatchVector3FielddictionaryConstructorTofvsPatchVector3FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchVector4Field::typeName(calculatedFvsPatchVector4Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchVector4Field::debug(
		std::string(calculatedFvsPatchVector4Field::typeName_()), 0, "");;
	fvsPatchVector4Field::addpatchConstructorToTable<calculatedFvsPatchVector4Field>
	addcalculatedFvsPatchVector4FieldpatchConstructorTofvsPatchVector4FieldTable_;
	fvsPatchVector4Field::addpatchMapperConstructorToTable<calculatedFvsPatchVector4Field>
	addcalculatedFvsPatchVector4FieldpatchMapperConstructorTofvsPatchVector4FieldTable_;
	fvsPatchVector4Field::adddictionaryConstructorToTable<calculatedFvsPatchVector4Field>
	addcalculatedFvsPatchVector4FielddictionaryConstructorTofvsPatchVector4FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchVector6Field::typeName(calculatedFvsPatchVector6Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchVector6Field::debug(
		std::string(calculatedFvsPatchVector6Field::typeName_()), 0, "");;
	fvsPatchVector6Field::addpatchConstructorToTable<calculatedFvsPatchVector6Field>
	addcalculatedFvsPatchVector6FieldpatchConstructorTofvsPatchVector6FieldTable_;
	fvsPatchVector6Field::addpatchMapperConstructorToTable<calculatedFvsPatchVector6Field>
	addcalculatedFvsPatchVector6FieldpatchMapperConstructorTofvsPatchVector6FieldTable_;
	fvsPatchVector6Field::adddictionaryConstructorToTable<calculatedFvsPatchVector6Field>
	addcalculatedFvsPatchVector6FielddictionaryConstructorTofvsPatchVector6FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchVector8Field::typeName(calculatedFvsPatchVector8Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchVector8Field::debug(
		std::string(calculatedFvsPatchVector8Field::typeName_()), 0, "");;
	fvsPatchVector8Field::addpatchConstructorToTable<calculatedFvsPatchVector8Field>
	addcalculatedFvsPatchVector8FieldpatchConstructorTofvsPatchVector8FieldTable_;
	fvsPatchVector8Field::addpatchMapperConstructorToTable<calculatedFvsPatchVector8Field>
	addcalculatedFvsPatchVector8FieldpatchMapperConstructorTofvsPatchVector8FieldTable_;
	fvsPatchVector8Field::adddictionaryConstructorToTable<calculatedFvsPatchVector8Field>
	addcalculatedFvsPatchVector8FielddictionaryConstructorTofvsPatchVector8FieldTable_;;

		
	template <>
	const ::tnbLib::word calculatedFvsPatchTensor2Field::typeName(calculatedFvsPatchTensor2Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchTensor2Field::debug(
		std::string(calculatedFvsPatchTensor2Field::typeName_()), 0, "");;
	fvsPatchTensor2Field::addpatchConstructorToTable<calculatedFvsPatchTensor2Field>
	addcalculatedFvsPatchTensor2FieldpatchConstructorTofvsPatchTensor2FieldTable_;
	fvsPatchTensor2Field::addpatchMapperConstructorToTable<calculatedFvsPatchTensor2Field>
	addcalculatedFvsPatchTensor2FieldpatchMapperConstructorTofvsPatchTensor2FieldTable_;
	fvsPatchTensor2Field::adddictionaryConstructorToTable<calculatedFvsPatchTensor2Field>
	addcalculatedFvsPatchTensor2FielddictionaryConstructorTofvsPatchTensor2FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchTensor3Field::typeName(calculatedFvsPatchTensor3Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchTensor3Field::debug(
		std::string(calculatedFvsPatchTensor3Field::typeName_()), 0, "");;
	fvsPatchTensor3Field::addpatchConstructorToTable<calculatedFvsPatchTensor3Field>
	addcalculatedFvsPatchTensor3FieldpatchConstructorTofvsPatchTensor3FieldTable_;
	fvsPatchTensor3Field::addpatchMapperConstructorToTable<calculatedFvsPatchTensor3Field>
	addcalculatedFvsPatchTensor3FieldpatchMapperConstructorTofvsPatchTensor3FieldTable_;
	fvsPatchTensor3Field::adddictionaryConstructorToTable<calculatedFvsPatchTensor3Field>
	addcalculatedFvsPatchTensor3FielddictionaryConstructorTofvsPatchTensor3FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchTensor4Field::typeName(calculatedFvsPatchTensor4Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchTensor4Field::debug(
		std::string(calculatedFvsPatchTensor4Field::typeName_()), 0, "");;
	fvsPatchTensor4Field::addpatchConstructorToTable<calculatedFvsPatchTensor4Field>
	addcalculatedFvsPatchTensor4FieldpatchConstructorTofvsPatchTensor4FieldTable_;
	fvsPatchTensor4Field::addpatchMapperConstructorToTable<calculatedFvsPatchTensor4Field>
	addcalculatedFvsPatchTensor4FieldpatchMapperConstructorTofvsPatchTensor4FieldTable_;
	fvsPatchTensor4Field::adddictionaryConstructorToTable<calculatedFvsPatchTensor4Field>
	addcalculatedFvsPatchTensor4FielddictionaryConstructorTofvsPatchTensor4FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchTensor6Field::typeName(calculatedFvsPatchTensor6Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchTensor6Field::debug(
		std::string(calculatedFvsPatchTensor6Field::typeName_()), 0, "");;
	fvsPatchTensor6Field::addpatchConstructorToTable<calculatedFvsPatchTensor6Field>
	addcalculatedFvsPatchTensor6FieldpatchConstructorTofvsPatchTensor6FieldTable_;
	fvsPatchTensor6Field::addpatchMapperConstructorToTable<calculatedFvsPatchTensor6Field>
	addcalculatedFvsPatchTensor6FieldpatchMapperConstructorTofvsPatchTensor6FieldTable_;
	fvsPatchTensor6Field::adddictionaryConstructorToTable<calculatedFvsPatchTensor6Field>
	addcalculatedFvsPatchTensor6FielddictionaryConstructorTofvsPatchTensor6FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchTensor8Field::typeName(calculatedFvsPatchTensor8Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchTensor8Field::debug(
		std::string(calculatedFvsPatchTensor8Field::typeName_()), 0, "");;
	fvsPatchTensor8Field::addpatchConstructorToTable<calculatedFvsPatchTensor8Field>
	addcalculatedFvsPatchTensor8FieldpatchConstructorTofvsPatchTensor8FieldTable_;
	fvsPatchTensor8Field::addpatchMapperConstructorToTable<calculatedFvsPatchTensor8Field>
	addcalculatedFvsPatchTensor8FieldpatchMapperConstructorTofvsPatchTensor8FieldTable_;
	fvsPatchTensor8Field::adddictionaryConstructorToTable<calculatedFvsPatchTensor8Field>
	addcalculatedFvsPatchTensor8FielddictionaryConstructorTofvsPatchTensor8FieldTable_;;

		
	template <>
	const ::tnbLib::word calculatedFvsPatchDiagTensor2Field::typeName(calculatedFvsPatchDiagTensor2Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchDiagTensor2Field::debug(
		std::string(calculatedFvsPatchDiagTensor2Field::typeName_()), 0, "");;
	fvsPatchDiagTensor2Field::addpatchConstructorToTable<calculatedFvsPatchDiagTensor2Field>
	addcalculatedFvsPatchDiagTensor2FieldpatchConstructorTofvsPatchDiagTensor2FieldTable_;
	fvsPatchDiagTensor2Field::addpatchMapperConstructorToTable<calculatedFvsPatchDiagTensor2Field>
	addcalculatedFvsPatchDiagTensor2FieldpatchMapperConstructorTofvsPatchDiagTensor2FieldTable_;
	fvsPatchDiagTensor2Field::adddictionaryConstructorToTable<calculatedFvsPatchDiagTensor2Field>
	addcalculatedFvsPatchDiagTensor2FielddictionaryConstructorTofvsPatchDiagTensor2FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchDiagTensor3Field::typeName(calculatedFvsPatchDiagTensor3Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchDiagTensor3Field::debug(
		std::string(calculatedFvsPatchDiagTensor3Field::typeName_()), 0, "");;
	fvsPatchDiagTensor3Field::addpatchConstructorToTable<calculatedFvsPatchDiagTensor3Field>
	addcalculatedFvsPatchDiagTensor3FieldpatchConstructorTofvsPatchDiagTensor3FieldTable_;
	fvsPatchDiagTensor3Field::addpatchMapperConstructorToTable<calculatedFvsPatchDiagTensor3Field>
	addcalculatedFvsPatchDiagTensor3FieldpatchMapperConstructorTofvsPatchDiagTensor3FieldTable_;
	fvsPatchDiagTensor3Field::adddictionaryConstructorToTable<calculatedFvsPatchDiagTensor3Field>
	addcalculatedFvsPatchDiagTensor3FielddictionaryConstructorTofvsPatchDiagTensor3FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchDiagTensor4Field::typeName(calculatedFvsPatchDiagTensor4Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchDiagTensor4Field::debug(
		std::string(calculatedFvsPatchDiagTensor4Field::typeName_()), 0, "");;
	fvsPatchDiagTensor4Field::addpatchConstructorToTable<calculatedFvsPatchDiagTensor4Field>
	addcalculatedFvsPatchDiagTensor4FieldpatchConstructorTofvsPatchDiagTensor4FieldTable_;
	fvsPatchDiagTensor4Field::addpatchMapperConstructorToTable<calculatedFvsPatchDiagTensor4Field>
	addcalculatedFvsPatchDiagTensor4FieldpatchMapperConstructorTofvsPatchDiagTensor4FieldTable_;
	fvsPatchDiagTensor4Field::adddictionaryConstructorToTable<calculatedFvsPatchDiagTensor4Field>
	addcalculatedFvsPatchDiagTensor4FielddictionaryConstructorTofvsPatchDiagTensor4FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchDiagTensor6Field::typeName(calculatedFvsPatchDiagTensor6Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchDiagTensor6Field::debug(
		std::string(calculatedFvsPatchDiagTensor6Field::typeName_()), 0, "");;
	fvsPatchDiagTensor6Field::addpatchConstructorToTable<calculatedFvsPatchDiagTensor6Field>
	addcalculatedFvsPatchDiagTensor6FieldpatchConstructorTofvsPatchDiagTensor6FieldTable_;
	fvsPatchDiagTensor6Field::addpatchMapperConstructorToTable<calculatedFvsPatchDiagTensor6Field>
	addcalculatedFvsPatchDiagTensor6FieldpatchMapperConstructorTofvsPatchDiagTensor6FieldTable_;
	fvsPatchDiagTensor6Field::adddictionaryConstructorToTable<calculatedFvsPatchDiagTensor6Field>
	addcalculatedFvsPatchDiagTensor6FielddictionaryConstructorTofvsPatchDiagTensor6FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchDiagTensor8Field::typeName(calculatedFvsPatchDiagTensor8Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchDiagTensor8Field::debug(
		std::string(calculatedFvsPatchDiagTensor8Field::typeName_()), 0, "");;
	fvsPatchDiagTensor8Field::addpatchConstructorToTable<calculatedFvsPatchDiagTensor8Field>
	addcalculatedFvsPatchDiagTensor8FieldpatchConstructorTofvsPatchDiagTensor8FieldTable_;
	fvsPatchDiagTensor8Field::addpatchMapperConstructorToTable<calculatedFvsPatchDiagTensor8Field>
	addcalculatedFvsPatchDiagTensor8FieldpatchMapperConstructorTofvsPatchDiagTensor8FieldTable_;
	fvsPatchDiagTensor8Field::adddictionaryConstructorToTable<calculatedFvsPatchDiagTensor8Field>
	addcalculatedFvsPatchDiagTensor8FielddictionaryConstructorTofvsPatchDiagTensor8FieldTable_;;

		
	template <>
	const ::tnbLib::word calculatedFvsPatchSphericalTensor2Field::typeName(
		calculatedFvsPatchSphericalTensor2Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchSphericalTensor2Field::debug(
		std::string(calculatedFvsPatchSphericalTensor2Field::typeName_()), 0, "");;
	fvsPatchSphericalTensor2Field::addpatchConstructorToTable<calculatedFvsPatchSphericalTensor2Field>
	addcalculatedFvsPatchSphericalTensor2FieldpatchConstructorTofvsPatchSphericalTensor2FieldTable_;
	fvsPatchSphericalTensor2Field::addpatchMapperConstructorToTable<calculatedFvsPatchSphericalTensor2Field>
	addcalculatedFvsPatchSphericalTensor2FieldpatchMapperConstructorTofvsPatchSphericalTensor2FieldTable_;
	fvsPatchSphericalTensor2Field::adddictionaryConstructorToTable<calculatedFvsPatchSphericalTensor2Field>
	addcalculatedFvsPatchSphericalTensor2FielddictionaryConstructorTofvsPatchSphericalTensor2FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchSphericalTensor3Field::typeName(
		calculatedFvsPatchSphericalTensor3Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchSphericalTensor3Field::debug(
		std::string(calculatedFvsPatchSphericalTensor3Field::typeName_()), 0, "");;
	fvsPatchSphericalTensor3Field::addpatchConstructorToTable<calculatedFvsPatchSphericalTensor3Field>
	addcalculatedFvsPatchSphericalTensor3FieldpatchConstructorTofvsPatchSphericalTensor3FieldTable_;
	fvsPatchSphericalTensor3Field::addpatchMapperConstructorToTable<calculatedFvsPatchSphericalTensor3Field>
	addcalculatedFvsPatchSphericalTensor3FieldpatchMapperConstructorTofvsPatchSphericalTensor3FieldTable_;
	fvsPatchSphericalTensor3Field::adddictionaryConstructorToTable<calculatedFvsPatchSphericalTensor3Field>
	addcalculatedFvsPatchSphericalTensor3FielddictionaryConstructorTofvsPatchSphericalTensor3FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchSphericalTensor4Field::typeName(
		calculatedFvsPatchSphericalTensor4Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchSphericalTensor4Field::debug(
		std::string(calculatedFvsPatchSphericalTensor4Field::typeName_()), 0, "");;
	fvsPatchSphericalTensor4Field::addpatchConstructorToTable<calculatedFvsPatchSphericalTensor4Field>
	addcalculatedFvsPatchSphericalTensor4FieldpatchConstructorTofvsPatchSphericalTensor4FieldTable_;
	fvsPatchSphericalTensor4Field::addpatchMapperConstructorToTable<calculatedFvsPatchSphericalTensor4Field>
	addcalculatedFvsPatchSphericalTensor4FieldpatchMapperConstructorTofvsPatchSphericalTensor4FieldTable_;
	fvsPatchSphericalTensor4Field::adddictionaryConstructorToTable<calculatedFvsPatchSphericalTensor4Field>
	addcalculatedFvsPatchSphericalTensor4FielddictionaryConstructorTofvsPatchSphericalTensor4FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchSphericalTensor6Field::typeName(
		calculatedFvsPatchSphericalTensor6Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchSphericalTensor6Field::debug(
		std::string(calculatedFvsPatchSphericalTensor6Field::typeName_()), 0, "");;
	fvsPatchSphericalTensor6Field::addpatchConstructorToTable<calculatedFvsPatchSphericalTensor6Field>
	addcalculatedFvsPatchSphericalTensor6FieldpatchConstructorTofvsPatchSphericalTensor6FieldTable_;
	fvsPatchSphericalTensor6Field::addpatchMapperConstructorToTable<calculatedFvsPatchSphericalTensor6Field>
	addcalculatedFvsPatchSphericalTensor6FieldpatchMapperConstructorTofvsPatchSphericalTensor6FieldTable_;
	fvsPatchSphericalTensor6Field::adddictionaryConstructorToTable<calculatedFvsPatchSphericalTensor6Field>
	addcalculatedFvsPatchSphericalTensor6FielddictionaryConstructorTofvsPatchSphericalTensor6FieldTable_;;
	template <>
	const ::tnbLib::word calculatedFvsPatchSphericalTensor8Field::typeName(
		calculatedFvsPatchSphericalTensor8Field::typeName_());
	template <>
	::tnbLib::debug::debugSwitch calculatedFvsPatchSphericalTensor8Field::debug(
		std::string(calculatedFvsPatchSphericalTensor8Field::typeName_()), 0, "");;
	fvsPatchSphericalTensor8Field::addpatchConstructorToTable<calculatedFvsPatchSphericalTensor8Field>
	addcalculatedFvsPatchSphericalTensor8FieldpatchConstructorTofvsPatchSphericalTensor8FieldTable_;
	fvsPatchSphericalTensor8Field::addpatchMapperConstructorToTable<calculatedFvsPatchSphericalTensor8Field>
	addcalculatedFvsPatchSphericalTensor8FieldpatchMapperConstructorTofvsPatchSphericalTensor8FieldTable_;
	fvsPatchSphericalTensor8Field::adddictionaryConstructorToTable<calculatedFvsPatchSphericalTensor8Field>
	addcalculatedFvsPatchSphericalTensor8FielddictionaryConstructorTofvsPatchSphericalTensor8FieldTable_;;

#undef doMakeFvsPatchTypeField

		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //