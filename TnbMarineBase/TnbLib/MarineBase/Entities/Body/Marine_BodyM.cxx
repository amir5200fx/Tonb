#include <Marine_CmpSection.hxx>
#include <Marine_BodyConstructor.hxx>
#include <Marine_Body_Wetted.hxx>
#include <Marine_BodyTools.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#define BodyCopy(BodyType)																		\
std::shared_ptr<BodyType> body;																	\
if(ShapeType())																					\
{																								\
	body = std::make_shared<BodyConstructor_Shape<BodyType>>();									\
	Debug_Null_Pointer(body);																	\
																								\
	auto t = std::dynamic_pointer_cast<BodyConstructor_Shape<BodyType>>(This());				\
	Debug_Null_Pointer(t);																		\
																								\
	std::dynamic_pointer_cast<BodyConstructor_Shape<BodyType>>(body)->SetShape(t->Shape());		\
																								\
	if(Marine_BodyTools::IsWetted(*body))														\
	{																							\
		auto w = std::dynamic_pointer_cast<BodyConstructor_Shape<Body_Wetted>>(This());			\
		Debug_Null_Pointer(w);																	\
																								\
		auto bw = std::dynamic_pointer_cast<BodyConstructor_Shape<Body_Wetted>>(body);			\
		Debug_Null_Pointer(bw);																	\
																								\
		bw->SetWL(w->WL());																		\
	}																							\
}																								\
else																							\
{																								\
	body = std::make_shared<BodyConstructor_noShape<BodyType>>();								\
	Debug_Null_Pointer(body);																	\
}																								\
																								\
body->SetIndex(Index());																		\
body->SetName(Name());																			\
																								\
if (NOT BaseLine().IsNull())																	\
{																								\
	body->SetBaseLine(BaseLine().BaseLine());													\
}																								\
																								\
auto& sections = body->ChangeSections();														\
sections.reserve(NbSections());																	\
for (const auto& x : body->Sections())															\
{																								\
	Debug_Null_Pointer(x);																		\
	auto c = x->Copy();																			\
																								\
	sections.push_back(std::move(c));															\
}																								\
return std::move(body);								
			