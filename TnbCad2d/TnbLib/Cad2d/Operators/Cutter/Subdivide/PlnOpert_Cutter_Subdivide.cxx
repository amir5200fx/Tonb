#include <PlnOpert_Cutter_Subdivide.hxx>

#include <PlnOpert_IntsctEntity.hxx>
#include <PlnOpert_IntsctPoint.hxx>
#include <PlnOpert_IntsctSegment2.hxx>
#include <PlnOpert_IntsctPair.hxx>
#include <PlnOpert_Cutter_Intersection.hxx>
#include <error.hxx>
#include <OSstream.hxx>

namespace tnbLib
{

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		CollectCutter
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctPair>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		entities.reserve(theEntities.size());
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);

			const auto& ent = x->Entity0();
			entities.push_back(ent);
			/*if (ent->IsPoint())
			{
				entities.push_back(x->Entity0());
			}
			else if (ent->IsSegment())
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(ent);
				Debug_Null_Pointer(seg);

				entities.push_back(seg->Start());
				entities.push_back(seg->End());
			}
			else
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> CollectCutter(Args)")
					<< "Invalid entity" << endl
					<< abort(FatalError);
			}*/
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		CollectEdges
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctPair>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		entities.reserve(theEntities.size());
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);

			const auto& ent = x->Entity1();
			entities.push_back(ent);
			/*if (ent->IsPoint())
			{
				entities.push_back(x->Entity1());
			}
			else if (ent->IsSegment())
			{
				auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(ent);
				Debug_Null_Pointer(seg);

				entities.push_back(seg->Start());
				entities.push_back(seg->End());
			}
			else
			{
				FatalErrorIn("std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> CollectCutter(Args)")
					<< "Invalid entity" << endl
					<< abort(FatalError);
			}*/
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		IntsctOnVertices
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->Paires().size() > 1)
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		IntsctOnSegments
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->IsSegment())
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		IntsctOnPoints
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theEntities
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& x : theEntities)
		{
			Debug_Null_Pointer(x);
			if (x->IsPoint() AND x->Paires().size() IS_EQUAL 1)
			{
				entities.push_back(x);
			}
		}
		return std::move(entities);
	}

	Standard_Boolean IsInside
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& thePt,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theSegment,
		const Standard_Real theTol
	)
	{
		if (NOT std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(thePt))
		{
			FatalErrorIn("Standard_Boolean IsInside(Args...)")
				<< "the entity is no the point type" << endl
				<< abort(FatalError);
		}

		auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(theSegment);
		if (NOT seg)
		{
			FatalErrorIn("Standard_Boolean IsInside(Args...)")
				<< "the entity is no the segment type" << endl
				<< abort(FatalError);
		}

		Debug_Null_Pointer(seg->Start());
		Debug_Null_Pointer(seg->End());

		const auto x0 = seg->Start()->CharParameter();
		const auto x1 = seg->End()->CharParameter();

		return INSIDE(thePt->CharParameter(), x0 - theTol, x1 + theTol);
	}

	void MergeVerticesWithSegments
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& theVt,
		const std::shared_ptr<PlnOpert_IntsctEntity>& theSegment,
		const Standard_Real theTol
	)
	{
		if (NOT std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(theVt))
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the point type" << endl
				<< abort(FatalError);
		}

		auto seg = std::dynamic_pointer_cast<PlnOpert_IntsctSegment2>(theSegment);
		if (NOT seg)
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the segment type" << endl
				<< abort(FatalError);
		}

		if (ABS(seg->Start()->CharParameter() - theVt->CharParameter()) <= theTol)
		{
			const auto& v = seg->Start();
			
			v->Paires().clear();
			for (const auto& x : theVt->Paires())
			{
				v->PushToPairs(x);
			}
		}
		else if (ABS(seg->End()->CharParameter() - theVt->CharParameter()) <= theTol)
		{
			const auto& v = seg->End();

			v->Paires().clear();
			for (const auto& x : theVt->Paires())
			{
				v->PushToPairs(x);
			}
		}
		else
		{
			FatalErrorIn("void MergeVerticesWithSegments(Args...)")
				<< "invalid intersection type" << endl
				<< abort(FatalError);
		}
	}

	void MergeVerticesWithPoints
	(
		const std::shared_ptr<PlnOpert_IntsctEntity>& theVt,
		const std::shared_ptr<PlnOpert_IntsctEntity>& thePt,
		const Standard_Real theTol
	)
	{
		if (NOT std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(theVt))
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the point type" << endl
				<< abort(FatalError);
		}

		auto pt = std::dynamic_pointer_cast<PlnOpert_IntsctPoint>(thePt);
		if (NOT pt)
		{
			FatalErrorIn("void MergeVertices(Args...)")
				<< "the entity is no the segment type" << endl
				<< abort(FatalError);
		}

		if (ABS(pt->CharParameter() - theVt->CharParameter()) <= theTol)
		{
			pt->Paires().clear();
			for (const auto& x : theVt->Paires())
			{
				pt->PushToPairs(x);
			}
		}
		else
		{
			FatalErrorIn("void MergeVerticesWithPoints(Args...)")
				<< "invalid intersection type" << endl
				<< abort(FatalError);
		}
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		RemoveCollideVerticesWithSegments
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theVertices,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theSegments,
			const Standard_Real theTol
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& v : theVertices)
		{
			Debug_Null_Pointer(v);

			Standard_Boolean flag = Standard_False;
			for (const auto& seg : theSegments)
			{
				Debug_Null_Pointer(seg);
				if (IsInside(v, seg, theTol))
				{
					MergeVerticesWithSegments(v, seg, theTol);

					flag = Standard_True;
					break;
				}
			}

			if (NOT flag)
			{
				entities.push_back(v);
			}
		}
		return std::move(entities);
	}

	std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>
		RemoveCollideVerticesWithPoints
		(
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& theVertices,
			const std::vector<std::shared_ptr<PlnOpert_IntsctEntity>>& thePoints,
			const Standard_Real theTol
		)
	{
		std::vector<std::shared_ptr<PlnOpert_IntsctEntity>> entities;
		for (const auto& v : theVertices)
		{
			Debug_Null_Pointer(v);

			Standard_Boolean flag = Standard_False;
			for (const auto& pt : thePoints)
			{
				Debug_Null_Pointer(pt);
				if (ABS(v->CharParameter() - pt->CharParameter()) <= theTol)
				{
					MergeVerticesWithPoints(v, pt, theTol);

					flag = Standard_True;
					break;
				}
			}

			if (NOT flag)
			{
				entities.push_back(v);
			}
		}
		return std::move(entities);
	}
}

void tnbLib::PlnOpert_Cutter_Subdivide::Perform(const Standard_Real theTol)
{
	const auto& intersection = Intersection();
	Debug_Null_Pointer(intersection);

	auto cutterEntities = CollectCutter(intersection->Entities());
	auto edgeEntities = CollectEdges(intersection->Entities());

	sort(cutterEntities.begin(), cutterEntities.end(), &PlnOpert_IntsctEntity::IsLess);

	auto intsctVertices = IntsctOnVertices(cutterEntities);
	auto intsctSegments = IntsctOnSegments(cutterEntities);
	auto intsctPoints = IntsctOnPoints(cutterEntities);

	auto removedCollideVerticesWithSegments = 
		RemoveCollideVerticesWithSegments(intsctVertices, intsctSegments, theTol);

	auto mergedVertices = 
		RemoveCollideVerticesWithPoints(removedCollideVerticesWithSegments, intsctPoints, theTol);


}