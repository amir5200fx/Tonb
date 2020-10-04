#include <SectPx_FieldFun.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_BinaryOpFieldFuns.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::SectPx_FieldFun::IsFieldFun() const
{
	return Standard_True;
}

typename tnbLib::sectPxLib::regObjType 
tnbLib::SectPx_FieldFun::RegObjType() const
{
	return sectPxLib::regObjType::fieldFun;
}

std::shared_ptr<tnbLib::SectPx_FieldFun>
tnbLib::operator+
(
	const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1
	)
{
	if (f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Sum
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "+" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (f0->IsRegistered() AND NOT f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Sum
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "+" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (NOT f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Sum
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "+" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else 
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Sum
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "+" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
}

std::shared_ptr<tnbLib::SectPx_FieldFun>
tnbLib::operator-
(
	const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1
	)
{
	if (f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Subtract
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "-" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (f0->IsRegistered() AND NOT f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Subtract
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "-" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (NOT f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Subtract
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "-" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Subtract
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "-" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
}

std::shared_ptr<tnbLib::SectPx_FieldFun>
tnbLib::operator*
(
	const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1
	)
{
	if (f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Cross
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "*" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (f0->IsRegistered() AND NOT f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Cross
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "*" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (NOT f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Cross
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "*" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Cross
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "*" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
}

std::shared_ptr<tnbLib::SectPx_FieldFun>
tnbLib::operator/
(
	const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1
	)
{
	if (f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Divide
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "/" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (f0->IsRegistered() AND NOT f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Divide
			<
			std::weak_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "/" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else if (NOT f0->IsRegistered() AND f1->IsRegistered())
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Divide
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::weak_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "/" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
	else
	{
		auto sum = std::make_shared
			<
			binaryOpsFieldFun::Divide
			<
			std::shared_ptr<SectPx_FieldFun>,
			std::shared_ptr<SectPx_FieldFun>
			>
			>();
		Debug_Null_Pointer(sum);

		sum->SetIndex(0);
		sum->SetName("(" + f0->Name() + "/" + f1->Name() + ")");

		sum->SetLeft(f0);
		sum->SetRight(f1);

		return std::move(sum);
	}
}