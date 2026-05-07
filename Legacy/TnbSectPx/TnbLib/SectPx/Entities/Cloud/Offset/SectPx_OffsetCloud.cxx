//#include <SectPx_OffsetCloud.hxx>
//
//tnbLib::SectPx_OffsetCloud::SectPx_OffsetCloud
//(
//	const Standard_Integer theIndex, 
//	const word & theName
//)
//	: SectPx_Cloud(theIndex, theName)
//{
//	// empty body
//}
//
//tnbLib::SectPx_OffsetCloud::SectPx_OffsetCloud
//(
//	const std::vector<Pnt2d>& theCoords
//)
//	: theCoords_(theCoords)
//{
//	// empty body
//}
//
//tnbLib::SectPx_OffsetCloud::SectPx_OffsetCloud
//(
//	const Standard_Integer theIndex, 
//	const word & theName, 
//	const std::vector<Pnt2d>& theCoords
//)
//	: SectPx_Cloud(theIndex, theName)
//	, theCoords_(theCoords)
//{
//	// empty body
//}
//
//tnbLib::SectPx_OffsetCloud::SectPx_OffsetCloud
//(
//	std::vector<Pnt2d>&& theCoords
//)
//	: theCoords_(std::move(theCoords))
//{
//	// empty body
//}
//
//tnbLib::SectPx_OffsetCloud::SectPx_OffsetCloud
//(
//	const Standard_Integer theIndex,
//	const word & theName, 
//	std::vector<Pnt2d>&& theCoords
//)
//	: SectPx_Cloud(theIndex, theName)
//	, theCoords_(std::move(theCoords))
//{
//	// empty body
//}
//
//std::vector<tnbLib::Pnt2d> 
//tnbLib::SectPx_OffsetCloud::GetCoords() const
//{
//	return theCoords_;
//}
//
//void tnbLib::SectPx_OffsetCloud::Import(const Pnt2d & theCoord)
//{
//	theCoords_.push_back(theCoord);
//}