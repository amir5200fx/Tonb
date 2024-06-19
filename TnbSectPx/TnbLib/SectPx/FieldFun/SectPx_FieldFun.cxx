#include <SectPx_FieldFun.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_BinaryOpFieldFuns.hxx>
#include <SectPx_UnaryOpFieldFuns.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

Standard_Boolean 
tnbLib::SectPx_FieldFun::IsFieldFun() const
{
	return Standard_True;
}

Standard_Boolean 
tnbLib::SectPx_FieldFun::IsParRegObj() const
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

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::min(const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1)
{
	if (f0->IsRegistered() AND f1->IsRegistered())
	{
		auto op = std::make_shared<binaryOpsFieldFun::Min<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);

		op->SetIndex(0);
		op->SetName("min(" + f0->Name() + "," + f1->Name() + ")");

		op->SetLeft(f0);
		op->SetRight(f1);
		return std::move(op);
	}
	if (f0->IsRegistered() AND NOT f1->IsRegistered())
	{
		auto op = std::make_shared<binaryOpsFieldFun::Min<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);

		op->SetIndex(0);
		op->SetName("min(" + f0->Name() + "," + f1->Name() + ")");

		op->SetLeft(f0);
		op->SetRight(f1);
		return std::move(op);
	}
	if (NOT f0->IsRegistered() AND f1->IsRegistered())
	{
		auto op = std::make_shared<binaryOpsFieldFun::Min<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);

		op->SetIndex(0);
		op->SetName("min(" + f0->Name() + "," + f1->Name() + ")");

		op->SetLeft(f0);
		op->SetRight(f1);
		return std::move(op);
	}
	auto op = std::make_shared<binaryOpsFieldFun::Min<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);

	op->SetIndex(0);
	op->SetName("min(" + f0->Name() + "," + f1->Name() + ")");

	op->SetLeft(f0);
	op->SetRight(f1);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::max(const std::shared_ptr<SectPx_FieldFun>& f0,
	const std::shared_ptr<SectPx_FieldFun>& f1)
{
	if (f0->IsRegistered() AND f1->IsRegistered())
	{
		auto op = std::make_shared<binaryOpsFieldFun::Max<std::weak_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);

		op->SetIndex(0);
		op->SetName("max(" + f0->Name() + "," + f1->Name() + ")");

		op->SetLeft(f0);
		op->SetRight(f1);
		return std::move(op);
	}
	if (f0->IsRegistered() AND NOT f1->IsRegistered())
	{
		auto op = std::make_shared<binaryOpsFieldFun::Max<std::weak_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);

		op->SetIndex(0);
		op->SetName("max(" + f0->Name() + "," + f1->Name() + ")");

		op->SetLeft(f0);
		op->SetRight(f1);
		return std::move(op);
	}
	if (NOT f0->IsRegistered() AND f1->IsRegistered())
	{
		auto op = std::make_shared<binaryOpsFieldFun::Max<std::shared_ptr<SectPx_FieldFun>, std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);

		op->SetIndex(0);
		op->SetName("max(" + f0->Name() + "," + f1->Name() + ")");

		op->SetLeft(f0);
		op->SetRight(f1);
		return std::move(op);
	}
	auto op = std::make_shared<binaryOpsFieldFun::Max<std::shared_ptr<SectPx_FieldFun>, std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);

	op->SetIndex(0);
	op->SetName("max(" + f0->Name() + "," + f1->Name() + ")");

	op->SetLeft(f0);
	op->SetRight(f1);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::sqrt(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Sqrt<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("sqrt(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Sqrt<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("sqrt(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::abs(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Abs<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("abs(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Abs<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("abs(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::sin(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Sin<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("sin(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Sin<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("sin(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::cos(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Cos<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("cos(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Cos<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("cos(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::tan(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Tan<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("tan(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Tan<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("tan(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::asin(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Asin<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("asin(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Asin<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("asin(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::acos(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Acos<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("acos(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Acos<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("acos(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}

std::shared_ptr<tnbLib::SectPx_FieldFun> tnbLib::atan(const std::shared_ptr<SectPx_FieldFun>& f)
{
	if (f->IsRegistered())
	{
		auto op = std::make_shared<unaryOpFieldFun::Atan<std::weak_ptr<SectPx_FieldFun>>>();
		Debug_Null_Pointer(op);
		op->SetIndex(0);
		op->SetName("atan(" + f->Name() + ")");

		op->SetField(f);
		return std::move(op);
	}
	auto op = std::make_shared<unaryOpFieldFun::Atan<std::shared_ptr<SectPx_FieldFun>>>();
	Debug_Null_Pointer(op);
	op->SetIndex(0);
	op->SetName("atan(" + f->Name() + ")");

	op->SetField(f);
	return std::move(op);
}
