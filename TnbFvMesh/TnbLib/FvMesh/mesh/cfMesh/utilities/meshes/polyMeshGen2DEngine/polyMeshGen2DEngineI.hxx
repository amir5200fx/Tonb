#pragma once
namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	inline const boolList& polyMeshGen2DEngine::activeFace() const
	{
		if (!activeFacePtr_)
			findActiveFaces();

		return *activeFacePtr_;
	}

	inline const labelList& polyMeshGen2DEngine::activeFaceLabels() const
	{
		if (!activeFaceLabelsPtr_)
			findActiveFaceLabels();

		return *activeFaceLabelsPtr_;
	}

	inline const boolList& polyMeshGen2DEngine::zMinPoints() const
	{
		if (!zMinPointPtr_)
			findZMinPoints();

		return *zMinPointPtr_;
	}

	inline const labelList& polyMeshGen2DEngine::zMinPointLabels() const
	{
		if (!zMinPointLabelsPtr_)
			findZMinPointLabels();

		return *zMinPointLabelsPtr_;
	}

	inline const labelList& polyMeshGen2DEngine::zMinToZMax() const
	{
		if (!zMinToZMaxPtr_)
			findZMinOffsetPoints();

		return *zMinToZMaxPtr_;
	}

	inline const boolList& polyMeshGen2DEngine::zMaxPoints() const
	{
		if (!zMaxPointPtr_)
			findZMaxPoints();

		return *zMaxPointPtr_;
	}

	inline const labelList& polyMeshGen2DEngine::zMaxPointLabels() const
	{
		if (!zMaxPointLabelsPtr_)
			findZMaxPointLabels();

		return *zMaxPointLabelsPtr_;
	}

	inline const labelList& polyMeshGen2DEngine::zMaxToZMin() const
	{
		if (!zMaxToZMinPtr_)
			findZMaxOffsetPoints();

		return *zMaxToZMinPtr_;
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //