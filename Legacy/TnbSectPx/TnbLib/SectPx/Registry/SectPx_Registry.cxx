#include <SectPx_Registry.hxx>

#include <SectPx_CountRegistry.hxx>
#include <SectPx_ScatterRegistry.hxx>
#include <SectPx_ParRegistry.hxx>
#include <SectPx_FrameRegistry.hxx>
#include <SectPx_ShapeRegistry.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

const std::string tnbLib::SectPx_Registry::extension = ".spxreg";

void tnbLib::SectPx_Registry::AllocateMemory()
{
	theCounter_ = std::make_shared<SectPx_CountRegistry>();
	theScatter_ = std::make_shared<SectPx_ScatterRegistry>();

	theParameter_ = std::make_shared<SectPx_ParRegistry>(theCounter_, theScatter_);
	theShape_ = std::make_shared<SectPx_ShapeRegistry>(theCounter_, theScatter_);
}

std::shared_ptr<tnbLib::SectPx_FrameRegistry> 
tnbLib::SectPx_Registry::SelectFrame
(
	const Standard_Integer theIndex
) const
{
	auto iter = theFrames_.find(theIndex);
	if (iter IS_EQUAL theFrames_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the frame doesn't exist" << ", id: " << theIndex << endl
			<< abort(FatalError);
	}
	return iter->second;
}

Standard_Integer
tnbLib::SectPx_Registry::CreateFrame()
{
	const auto id = FrameCounter().RetrieveIndex();
	static const auto name = "frame";

	auto frame = std::make_shared<SectPx_FrameRegistry>(theCounter_, theScatter_);
	Debug_Null_Pointer(frame);

	frame->SetIndex(id);
	frame->SetName(name + std::to_string(id));

	auto paired = std::make_pair(id, std::move(frame));
	auto insert = theFrames_.insert(std::move(paired));
	Debug_If_Condition(NOT insert.second);
	return id;
}

std::shared_ptr<tnbLib::SectPx_FrameRegistry> 
tnbLib::SectPx_Registry::RemoveFrame
(
	const Standard_Integer theIndex
)
{
	auto iter = theFrames_.find(theIndex);
	if (iter IS_EQUAL theFrames_.end())
	{
		FatalErrorIn(FunctionSIG)
			<< " the frame doesn't exist" << ", id: " << theIndex << endl
			<< abort(FatalError);
	}
	auto item = std::move(iter->second);
	theFrames_.erase(iter);
	return std::move(item);
}