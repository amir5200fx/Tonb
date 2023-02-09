#pragma once
template<class T, bool Bounded>
inline void tnbLib::NumAlg_GA<T, Bounded>::Iterate()
{
	if (CurrentGeneration() >= GaInfo()->MaxNbGenerations())
	{
		FatalErrorIn(" void Iterate()")
			<< " Exceed nb. of iterations"
			<< abort(FatalError);
	}

	if (!IsInitiated())
	{
		Initiate();
	}

	CurrentGenRef()++;

	auto& pop = PopInfo()->Population();
	Standard_Integer K;

	if (verbose)
	{
		std::cout << " Generation Nb. " << CurrentGeneration() << " of " << GaInfo()->MaxNbGenerations() << "\n";
	}

	K = 0;
	for (auto& x : Memory().cost)
		x = Value(*pop[K++], Object());
	
	K = 0;
	for (auto& x : Memory().ind)
		x = K++;

	{ // Sort the cost list [2/7/2023 Payvand]
		std::vector<std::pair<Standard_Real, Standard_Integer>> sortedList;
		sortedList.reserve(Memory().ind.size());
		for (size_t i = 0; i < Memory().ind.size(); i++)
		{
			auto paired = std::make_pair(Memory().cost.at(i), Memory().ind.at(i));
			sortedList.push_back(paired);
		}

		std::sort(sortedList.begin(), sortedList.end(), [](const std::pair<Standard_Real, Standard_Integer>& p0, const std::pair<Standard_Real, Standard_Integer>& p1)->auto {return p0.first < p1.first; });

		for (size_t i = 0; i < sortedList.size(); i++)
		{
			Memory().cost.at(i) = sortedList.at(i).first;
			Memory().ind.at(i) = sortedList.at(i).second;
		}
	}
	
	forThose(i, 0, Memory().popsize - 1)
	{
		forThose(j, 0, Memory().npar - 1)
			Memory().par2[i][j] = pop[i]->operator[](j);
	}

	forThose(i, 0, Memory().popsize - 1)
	{
		forThose(j, 0, Memory().npar - 1)
			pop[i]->operator[](j) = Memory().par2[Memory().ind[i]][j];
	}
	
	// Pair chromosomes and produce offspring
	Memory().odds[0] = 0;

	forThose(i, 0, Memory().keep - 1) Memory().odds[i + 1] = Memory().keep - i;

	sumPrefix(Memory().odds);

	auto tmp = Memory().odds[Memory().keep];
	forThose(i, 1, Memory().odds.size() - 1) Memory().odds[i] /= tmp;
	
	Initialize(Memory().pick1);
	Initialize(Memory().pick2);

	forThose(i, 0, Memory().m - 1)
	{
		forThose(j, 1, Memory().keep)
		{
			if (Memory().pick1[i] <= Memory().odds[j] && Memory().pick1[i] > Memory().odds[j - 1]) Memory().ma[i] = j - 1;
			if (Memory().pick2[i] <= Memory().odds[j] && Memory().pick2[i] > Memory().odds[j - 1]) Memory().pa[i] = j - 1;
		}
	}
	
	forThose(i, 0, ceil(((Standard_Real)Memory().keep) / 2) - 1)
		Memory().ix[i] = 2 * i;

	Initialize(Memory().temp_arr_1);

	forThose(i, 0, Memory().m - 1)
		Memory().xp[i] = (Standard_Integer)MAX(0.0, ceil(Memory().npar * Memory().temp_arr_1[i]) - 1);

	Initialize(Memory().r);
	std::cout << "h0" << std::endl;
	forThose(i, 0, Memory().m - 1)
	{
		auto xy = pop[Memory().ma[i]]->operator[](Memory().xp[i]) - pop[Memory().pa[i]]->operator[](Memory().xp[i]);
		forThose(j, 0, Memory().npar - 1)
		{
			pop[Memory().keep + Memory().ix[i] - 1]->operator[](j) = pop[Memory().ma[i]]->operator[](j);
			pop[Memory().keep + Memory().ix[i]]->operator[](j) = pop[Memory().pa[i]]->operator[](j);
		}

		pop[Memory().keep + Memory().ix[i] - 1]->operator[](Memory().xp[i]) = pop[Memory().ma[i]]->operator[](Memory().xp[i]) - Memory().r[i] * xy;
		pop[Memory().keep + Memory().ix[i]]->operator[](Memory().xp[i]) = pop[Memory().pa[i]]->operator[](Memory().xp[i]) + Memory().r[i] * xy;

		if (Memory().xp[i] < Memory().npar)
		{
			forThose(j, 0, Memory().xp[j] - 1)
			{
				pop[Memory().keep + Memory().ix[i] - 1]->operator[](j) = pop[Memory().keep + Memory().ix[i] - 1]->operator[](j);
				pop[Memory().keep + Memory().ix[i]]->operator[](j) = pop[Memory().keep + Memory().ix[i]]->operator[](j);
			}

			forThose(j, Memory().xp[i], Memory().npar - 1)
			{
				pop[Memory().keep + Memory().ix[i] - 1]->operator[](j) = pop[Memory().keep + Memory().ix[i]]->operator[](j);
				pop[Memory().keep + Memory().ix[i]]->operator[](j) = pop[Memory().keep + Memory().ix[i] - 1]->operator[](j);
			}
		}
	}
	std::cout << "h1" << std::endl;
	// mutate the population
	Initialize(Memory().temp_arr_2);

	forThose(i, 0, Memory().nmut - 1)
		Memory().mrow[i] = (Standard_Integer)MAX(0.0, ceil(Memory().temp_arr_2[i] * (Memory().popsize - 1)));

	std::sort(Memory().mrow.begin(), Memory().mrow.end());
	
	Initialize(Memory().temp_arr_2);

	forThose(i, 0, Memory().nmut - 1)
		Memory().mcol[i] = (Standard_Integer)MAX(0.0, ceil(Memory().temp_arr_2[i] * Memory().npar) - 1);

	Initialize(Memory().temp_arr_2);

	MutNormalize(Memory().mrow, Memory().mcol, Memory().temp_arr_2);

	if (CurrentGeneration() >= GaInfo()->MaxNbGenerations())
	{
		Change_IsDone() = Standard_True;
	}
}

template<class T, bool Bounded>
inline void tnbLib::NumAlg_GA<T, Bounded>::Perform()
{
	if (!IsInitiated())
	{
		Initiate();
	}

	// start generation
	//auto minc = (Standard_Real)0.;

	while (CurrentGeneration() < GaInfo()->MaxNbGenerations())
	{
		Iterate();
	}
}