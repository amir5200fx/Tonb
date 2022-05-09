#pragma once
template<class Function>
inline Standard_Real tnbLib::NumAlg_NelderMead<Function>::Size() const
{
	auto norm = (Standard_Real)0.0;
	auto best = Variable(cache::Lo);
	for (int i = 0; i <= NbVariables(); i++)
	{
		//auto s = fun::SquareTwoNorm(best, Variable(i));
		auto s = (Standard_Real)0.0;
		for (int k = 1; k <= NbVariables(); k++)
		{
			auto d = fun::V(k, Variable(cache::Lo)) - fun::V(k, Variable(i));
			s += d * d;
		}
		if (s > norm) norm = s;
	}
	return sqrt(norm);
}

template<class Function>
inline void tnbLib::NumAlg_NelderMead<Function>::Order()
{
	cache::Lo = 0;
	cache::Hi = 0;
	for (int i = 1; i <= NbVariables(); i++)
	{
		if (Y(i) < Y(cache::Lo)) cache::Lo = i;
		if (Y(i) > Y(cache::Hi)) cache::Hi = i;
	}
	cache::Li = cache::Hi;
	cache::Ho = cache::Lo;

	for (int i = 0; i <= NbVariables(); i++)
	{
		if (i NOT_EQUAL cache::Lo AND Y(i) < Y(cache::Li)) cache::Li = i;
		if (i NOT_EQUAL cache::Hi AND Y(i) > Y(cache::Ho)) cache::Ho = i;
	}
}

template<class Function>
inline void tnbLib::NumAlg_NelderMead<Function>::NewPoints()
{
	for (int k = 1; k <= NbVariables(); k++)
	{
		auto s = (Standard_Real)0.0;
		for (int j = 0; j <= NbVariables(); j++)
		{
			s += fun::V(k, Variable(j));
		}
		fun::SetV(k, (s - fun::V(k, Variable(cache::Hi))) / (Standard_Real)NbVariables(), cache::M);
	}

	for (int k = 1; k <= NbVariables(); k++)
	{
		fun::SetV(k, coeff::ExpansionCoeff() * fun::V(k, cache::M) - fun::V(k, Variable(cache::Hi)), cache::R);
	}

	cache::YR = fun::Value(cache::R);
}

template<class Function>
inline void tnbLib::NumAlg_NelderMead<Function>::Shrink()
{
	for (int j = 0; j <= NbVariables(); j++)
	{
		if (j NOT_EQUAL cache::Lo)
		{
			for (int k = 1; k <= NbVariables(); k++)
			{
				fun::SetV(k, coeff::ShrinkCoeff()*(fun::V(k, Variable(j)) + fun::V(k, Variable(cache::Lo))), ChangeVariable(j));
			}
			ChangeY(j) = fun::Value(Variable(j));
		}
	}
}

template<class Function>
inline void tnbLib::NumAlg_NelderMead<Function>::Replace()
{
	auto& var = ChangeVariable(cache::Hi);
	for (int k = 1; k <= NbVariables(); k++)
	{
		fun::SetV(k, fun::V(k, cache::R), var);
	}
	ChangeY(cache::Hi) = cache::YR;
}

template<class Function>
inline void tnbLib::NumAlg_NelderMead<Function>::Improve()
{
	if (cache::YR < Y(cache::Ho))
	{
		if (Y(cache::Li) < cache::YR)
		{
			Replace();
		}
		else
		{
			for (int k = 1; k <= NbVariables(); k++)
				fun::SetV(k, coeff::ExpansionCoeff() * fun::V(k, cache::R) - fun::V(k, cache::M), cache::E);
			cache::YE = fun::Value(cache::E);

			if (cache::YE < Y(cache::Li))
			{
				for (int k = 1; k <= NbVariables(); k++)
					fun::SetV(k, fun::V(k, cache::E), ChangeVariable(cache::Hi));
				ChangeY(cache::Hi) = cache::YE;
			}
			else
			{
				Replace();
			}
		}
	}
	else
	{
		if (cache::YR < Y(cache::Hi))
		{
			Replace();
		}

		for (int k = 1; k <= NbVariables(); k++)
			fun::SetV(k, coeff::ContractionCoeff()*(fun::V(k, Variable(cache::Hi)) + fun::V(k, cache::M)), cache::C);

		cache::YC = fun::Value(cache::C);

		if (cache::YC < Y(cache::Hi))
		{
			for (int k = 1; k <= NbVariables(); k++)
				fun::SetV(k, fun::V(k, cache::C), ChangeVariable(cache::Hi));
			ChangeY(cache::Hi) = cache::YC;
		}
		else
		{
			Shrink();
		}
	}
}

template<class Function>
inline void tnbLib::NumAlg_NelderMead<Function>::Perform()
{
	if (NOT AlgInfo())
	{
		FatalErrorIn(FunctionSIG)
			<< "no info has been found!" << endl
			<< abort(FatalError);
	}

	fun::Initial(theVariables_);

	for (int j = 0; j <= NbVariables(); j++)
		ChangeY(j) = fun::Value(Variable(j));

	Order();

	Standard_Integer Iter = 0;
	IsConv = Standard_False;

	while (NOT fun::IsConverged() AND Iter < AlgInfo()->MaxNbIterations())
	{
		std::cout << "iteration: " << Iter << std::endl;
		NewPoints();

		Improve();

		Order();

		Iter++;

		std::cout << std::endl;
	}

	if (Iter < AlgInfo()->MaxNbIterations())
	{
		IsConv = Standard_True;
	}
}