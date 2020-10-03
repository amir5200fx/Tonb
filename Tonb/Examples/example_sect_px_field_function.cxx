#include <Tnb_Examples.hxx>

#include <SectPx_Pars.hxx>
#include <SectPx_FieldFun_Uni.hxx>
#include <SectPx_FieldFun_Expr.hxx>

void tnbLib::example_sect_px_field_function()
{
	auto p0 = std::make_shared<SectPx_FixedPar>(4.0);
	p0->SetIndex(1);
	p0->SetName("parameter 1");

	auto p1 = std::make_shared<SectPx_FixedPar>(2.5);
	p1->SetIndex(2);
	p1->SetName("parameter 2");

	auto f0 = std::make_shared<sectPxLib::FieldFun_Uni>();
	f0->SetPar(p0);
	f0->SetName("field 1");

	auto f1 = std::make_shared<sectPxLib::FieldFun_Uni>();
	f1->SetPar(p1);
	f1->SetName("field 2");

	auto f2 = std::make_shared<sectPxLib::FieldFun_Expr>("2 * pi * x");
	f2->SetName("field 3");

	f2->AddVariable("x", *p1);

	auto sum = (f0*(f0 + f1) - f2 * (f0 - f1));

	auto f3 = std::make_shared<sectPxLib::FieldFun_Expr>("2 * x ^ 2");
	f3->SetName("field 4");

	f3->AddVariable("x", *sum);

	auto sum1 = sum + f3;

	cout << sum1->Name() << " , value = " << sum1->Value() << std::endl;
}