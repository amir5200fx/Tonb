#include <SeriesProps_WagenB_Section.hxx>

#include <SeriesProps_TabulatedWagenB_V1.hxx>
#include <SeriesProps_TabulatedWagenB_V2.hxx>
#include <Geo2d_AirfoilFace.hxx>
#include <Geo2d_AirfoilBack.hxx>
#include <Geo_xDistb.hxx>
#include <Pnt2d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

void tnbLib::SeriesProps_WagenB_Section::Perform
(
	const std::shared_ptr<Geo_xDistb>& theDistb
)
{
	if (NOT theDistb)
	{
		FatalErrorIn(FunctionSIG)
			<< "no distb. fun. has been loaded!" << endl
			<< abort(FatalError);
	}

	Debug_Null_Pointer(seriesProps::gl_wagenB_V1_values);
	Debug_Null_Pointer(seriesProps::gl_wagenB_V2_values);

	const auto& v1Table = *seriesProps::gl_wagenB_V1_values;
	const auto& v2Table = *seriesProps::gl_wagenB_V2_values;

	std::vector<Pnt2d> faces, backs;
	faces.reserve(theDistb->Size());
	backs.reserve(theDistb->Size());

	for (auto x : theDistb->Values())
	{
		auto v1 = v1Table.Value(Radius(), x);
		auto v2 = v2Table.Value(Radius(), x);

		if (x <= 0)
		{
			auto dt = MaxThick() - TrailingThick();
			Debug_If_Condition(dt < 0);

			auto yface = v1 * dt;
			auto yback = (v1 + v2)*dt + TrailingThick();

			Pnt2d pface(x * (Chord() - B()), yface);
			Pnt2d pback(x * (Chord() - B()), yback);

			faces.push_back(std::move(pface));
			backs.push_back(std::move(pback));
		}
		else
		{
			auto dt = MaxThick() - LeadingThick();
			Debug_If_Condition(dt < 0);

			auto yface = v1 * dt;
			auto yback = (v1 + v2)*dt + LeadingThick();

			Pnt2d pface(x * B(), yface);
			Pnt2d pback(x * B(), yback);

			faces.push_back(std::move(pface));
			backs.push_back(std::move(pback));
		}
	}

	auto faceSurf = std::make_shared<Geo2d_AirfoilFace>(std::move(faces));
	auto backSurf = std::make_shared<Geo2d_AirfoilBack>(std::move(backs));

	FaceSurfaceRef() = std::move(faceSurf);
	BackSurfaceRef() = std::move(backSurf);
	Change_IsDone() = Standard_True;
}