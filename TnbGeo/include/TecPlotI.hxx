#pragma once
#include <Pnt2d.hxx>
#include <Pnt3d.hxx>
#include <TnbError.hxx>
#include <OSstream.hxx>

#include "TecPlot.hxx"

namespace tnbLib
{
	namespace Io
	{

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			OFstream & File
		)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteField()") << "\n"
					<< "the Field's size and the Points' size aren't equal.\n"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(File);
				File << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					File << x[I] << "  ";
				File << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void WriteField(const std::vector<std::array<Type, nbVAR>>& var, const std::vector<Pnt2d>& thePoints,
			std::stringstream& theStream)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteField()") << "\n"
					<< "the Field's size and the Points' size aren't equal.\n"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(theStream);
				theStream << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					theStream << x[I] << "  ";
				theStream << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void WriteField(const std::vector<std::array<Type, nbVAR>>& var, const std::vector<Pnt2d>& thePoints,
		                std::fstream& file)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteField()") << "\n"
					<< "the Field's size and the Points' size aren't equal.\n"
					<< abort(FatalError);
			}
			forThose(Index, 0, StlMaxIndexOf(thePoints))
			{
				thePoints.at(Index).AddToPlt(file);
				file << " ";
				forThose(I, 0, nbVAR - 1)
				{
					file << var.at(Index).at(I) << " ";
				}
				file << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void WriteField
		(
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			OFstream & File
		)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteField()") << "\n"
					<< "the Field's size and the Points' size aren't equal.\n"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(File);
				File << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					File << x[I] << "  ";
				File << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void WriteField(const std::vector<std::array<Type, nbVAR>>& var, const std::vector<Pnt3d>& thePoints,
			std::stringstream& theStream)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteField()") << "\n"
					<< "the Field's size and the Points' size aren't equal.\n"
					<< abort(FatalError);
			}

			forThose(Index, 0, thePoints.size() - 1)
			{
				thePoints[Index].AddToPlt(theStream);
				theStream << "  ";
				const auto& x = var[Index];
				forThose(I, 0, nbVAR - 1)
					theStream << x[I] << "  ";
				theStream << "\n";
			}
		}

		template <class Type, size_t nbVAR>
		void WriteField(const std::vector<std::array<Type, nbVAR>>& var, const std::vector<Pnt3d>& thePoints,
			std::fstream& file)
		{
			if (var.size() != thePoints.size())
			{
				FatalErrorIn("void WriteField()") << "\n"
					<< "the Field's size and the Points' size aren't equal.\n"
					<< abort(FatalError);
			}
			forThose(Index, 0, StlMaxIndexOf(thePoints))
			{
				thePoints.at(Index).AddToPlt(file);
				file << " ";
				forThose(I, 0, nbVAR - 1)
				{
					file << var.at(Index).at(I) << " ";
				}
				file << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField
		(
			const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var,
			OFstream & File
		)
		{
			if (var.size() != Triangles.size())
			{
				FatalErrorIn("void WriteCellCenteredField()") << "\n"
					<< "The Field's size and the Connectivity list's size aren't equal.\n"
					<< abort(FatalError);
			}

			for (const auto& x : var)
			{
				forThose(Index, 0, nbVAR - 1)
					File << x[Index] << "  ";
				File << endl;
			}

			for (const auto& x : Triangles)
			{
				File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void WriteCellCenteredField(const std::vector<connectivity::triple>& Triangles,
			const std::vector<std::array<Type, nbVAR>>& var, std::stringstream& theStream)
		{
			if (var.size() != Triangles.size())
			{
				FatalErrorIn("void WriteCellCenteredField()") << "\n"
					<< "The Field's size and the Connectivity list's size aren't equal.\n"
					<< abort(FatalError);
			}

			for (const auto& x : var)
			{
				forThose(Index, 0, nbVAR - 1)
					theStream << x[Index] << "  ";
				theStream << "\n";
			}

			for (const auto& x : Triangles)
			{
				theStream << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void WriteCellCenteredField(const std::vector<connectivity::triple>& Triangles, const std::vector<std::array<Type, nbVAR>>& var, std::fstream& file)
		{
			if (var.size() != Triangles.size())
			{
				FatalErrorIn("void WriteCellCenteredField()") << "\n"
					<< "The Field's size and the Connectivity list's size aren't equal.\n"
					<< abort(FatalError);
			}
			for (const auto& v: var)
			{
				forThose(Index, 0, nbVAR - 1)
				{
					file << v.at(Index) << " ";
				}
				file << "\n";
			}
			for (const auto& t: Triangles)
			{
				file << t.Value(0)
					<< " "
					<< t.Value(1)
					<< " "
					<< t.Value(2)
					<< "\n";
			}
		}

		template <class Type, size_t nbVAR>
		void WriteCellCenteredField(const std::vector<connectivity::quadruple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var, OFstream& file)
		{
			if (ids.size() != var.size())
			{
				FatalErrorIn("void WriteCellCenteredField()") << "\n"
					<< "The Field's size and the Connectivity list's size aren't equal.\n"
					<< abort(FatalError);
			}
			for (const auto& v : var)
			{
				forThose(Index, 0, nbVAR - 1)
				{
					file << v.at(Index) << " ";
				}
				file << "\n";
			}
			for (const auto& i: ids)
			{
				file << i.Value(0)
					<< " "
					<< i.Value(1)
					<< " "
					<< i.Value(2)
					<< " "
					<< i.Value(3)
					<< "\n";
			}
		}

		template <class Type, size_t nbVAR>
		void WriteCellCenteredField(const std::vector<connectivity::quadruple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var, std::stringstream& file)
		{
			if (ids.size() != var.size())
			{
				FatalErrorIn("void WriteCellCenteredField()") << "\n"
					<< "The Field's size and the Connectivity list's size aren't equal.\n"
					<< abort(FatalError);
			}
			for (const auto& v : var)
			{
				forThose(Index, 0, nbVAR - 1)
				{
					file << v.at(Index) << " ";
				}
				file << "\n";
			}
			for (const auto& i : ids)
			{
				file << i.Value(0)
					<< " "
					<< i.Value(1)
					<< " "
					<< i.Value(2)
					<< " "
					<< i.Value(3)
					<< "\n";
			}
		}

		template <class Type, size_t nbVAR>
		void WriteCellCenteredField(const std::vector<connectivity::quadruple>& ids,
			const std::vector<std::array<Type, nbVAR>>& var, std::fstream& file)
		{
			if (ids.size() != var.size())
			{
				FatalErrorIn("void WriteCellCenteredField()") << "\n"
					<< "The Field's size and the Connectivity list's size aren't equal.\n"
					<< abort(FatalError);
			}
			for (const auto& v : var)
			{
				forThose(Index, 0, nbVAR - 1)
				{
					file << v.at(Index) << " ";
				}
				file << "\n";
			}
			for (const auto& i : ids)
			{
				file << i.Value(0)
					<< " "
					<< i.Value(1)
					<< " "
					<< i.Value(2)
					<< " "
					<< i.Value(3)
					<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream & File
		)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			File << Variables << endl;

			WriteFeTriangleZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				File
			);

			WriteField
			(
				var,
				thePoints,
				File
			);

			for (const auto& x : Triangles)
			{
				File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints, const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			theStream << Variables << "\n";

			WriteFeTriangleZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				theStream
			);

			WriteField
			(
				var,
				thePoints,
				theStream
			);

			for (const auto& x : Triangles)
			{
				theStream
					<< x.Value(0)
					<< "  "
					<< x.Value(1)
					<< "  "
					<< x.Value(2)
					<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream & File
		)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			File << Variables << endl;

			WriteFeTriangleZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				File
			);

			WriteField
			(
				var,
				thePoints,
				File
			);

			for (const auto& x : Triangles)
			{
				File << x.Value(0) << "  " << x.Value(1) << "  " << x.Value(2) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			theStream << Variables << "\n";

			WriteFeTriangleZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				theStream
			);

			WriteField
			(
				var,
				thePoints,
				theStream
			);

			for (const auto& x : Triangles)
			{
				theStream
				<< x.Value(0)
				<< "  "
				<< x.Value(1)
				<< "  "
				<< x.Value(2)
				<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField
		(
			const word& theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints,
			const std::vector<connectivity::quadruple>& theTets,
			OFstream& File
		)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			File << Variables << endl;

			WriteFeTetrahedralZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theTets.size()),
				File
			);

			WriteField
			(
				var,
				thePoints,
				File
			);

			for (const auto& x : theTets)
			{
				File << x.Value(0) << " " << x.Value(1) << " " << x.Value(2) << " " << x.Value(3) << endl;
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::quadruple>& theTets,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			theStream << Variables << endl;

			WriteFeTetrahedralZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theTets.size()),
				theStream
			);

			WriteField
			(
				var,
				thePoints,
				theStream
			);

			for (const auto& x : theTets)
			{
				theStream
				<< x.Value(0)
				<< " "
				<< x.Value(1)
				<< " "
				<< x.Value(2)
				<< " "
				<< x.Value(3)
				<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
		                 const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements,
		                 OFstream& file)
		{
			file << "VARIABLES = X Y Z" + theVarNames << "\n";
			WriteFeHexahedralZone(static_cast<Standard_Integer>(thePoints.size()),
			                      static_cast<Standard_Integer>(theElements.size()), file);

			WriteField(var, thePoints, file);

			for (const auto& x: theElements)
			{
				file
					<< x.Value(0)
					<< " "
					<< x.Value(1)
					<< " "
					<< x.Value(2)
					<< " "
					<< x.Value(3)
					<< " "
					<< x.Value(4)
					<< " "
					<< x.Value(5)
					<< " "
					<< x.Value(6)
					<< " "
					<< x.Value(7)
					<< "\n";
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements,
			std::stringstream& file)
		{
			file << "VARIABLES = X Y Z" + theVarNames << "\n";
			WriteFeHexahedralZone(static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theElements.size()), file);

			WriteField(var, thePoints, file);

			for (const auto& x : theElements)
			{
				file
					<< x.Value(0)
					<< " "
					<< x.Value(1)
					<< " "
					<< x.Value(2)
					<< " "
					<< x.Value(3)
					<< " "
					<< x.Value(4)
					<< " "
					<< x.Value(5)
					<< " "
					<< x.Value(6)
					<< " "
					<< x.Value(7)
					<< "\n";
			}
		}

		template <class Type, size_t nbVAR>
		void ExportField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements,
			std::fstream& file)
		{
			file << "VARIABLES = X Y Z" + theVarNames << "\n";
			WriteFeHexahedralZone(static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theElements.size()), file);

			WriteField(var, thePoints, file);

			for (const auto& x : theElements)
			{
				file
					<< x.Value(0)
					<< " "
					<< x.Value(1)
					<< " "
					<< x.Value(2)
					<< " "
					<< x.Value(3)
					<< " "
					<< x.Value(4)
					<< " "
					<< x.Value(5)
					<< " "
					<< x.Value(6)
					<< " "
					<< x.Value(7)
					<< "\n";
			}
		}

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField
		(
			const word & theVarNames,
			const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints,
			const std::vector<connectivity::triple>& Triangles,
			OFstream & File
		)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			File << Variables << endl;

			WriteCellCenteredFeTriangularZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				static_cast<Standard_Integer>(nbVAR), File);

			WritePointsVariables(thePoints, File);

			WriteCellCenteredField(Triangles, var, File);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt2d>& thePoints, const std::vector<connectivity::triple>& Triangles,
			std::stringstream& theStream)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			theStream << Variables << "\n";

			WriteCellCenteredFeTriangularZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				static_cast<Standard_Integer>(nbVAR), theStream);

			WritePointsVariables(thePoints, theStream);

			WriteCellCenteredField(Triangles, var, theStream);
		}

		template<class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
		                             const std::vector<Pnt2d>& thePoints,
		                             const std::vector<connectivity::triple>& Triangles, std::fstream& file)
		{
			word Variables = "VARIABLES = X Y " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeTriangularZone
			(
				static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(Triangles.size()),
				static_cast<Standard_Integer>(nbVAR), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(Triangles, var, file);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::quadruple>& theElements,
			OFstream& file)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeTetrahedralZone(static_cast<Standard_Integer>(thePoints.size()),
			                                   static_cast<Standard_Integer>(theElements.size()),
			                                   static_cast<Standard_Integer>(nbVAR), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(theElements, var, file);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::quadruple>& theElements,
			std::stringstream& file)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeTetrahedralZone(static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theElements.size()),
				static_cast<Standard_Integer>(nbVAR), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(theElements, var, file);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::quadruple>& theElements,
			std::fstream& file)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeTetrahedralZone(static_cast<Standard_Integer>(thePoints.size()),
			                                  static_cast<Standard_Integer>(theElements.size()),
			                                  static_cast<Standard_Integer>(var.size()), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(theElements, var, file);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements, OFstream& file)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeHexadedralZone(static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theElements.size()),
				static_cast<Standard_Integer>(var.size()), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(theElements, var, file);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements,
			std::stringstream& file)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeHexadedralZone(static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theElements.size()),
				static_cast<Standard_Integer>(var.size()), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(theElements, var, file);
		}

		template <class Type, size_t nbVAR>
		void ExportCellCenteredField(const word& theVarNames, const std::vector<std::array<Type, nbVAR>>& var,
			const std::vector<Pnt3d>& thePoints, const std::vector<connectivity::octuple>& theElements,
			std::fstream& file)
		{
			word Variables = "VARIABLES = X Y Z " + theVarNames;
			file << Variables << "\n";

			WriteCellCenteredFeHexadedralZone(static_cast<Standard_Integer>(thePoints.size()),
				static_cast<Standard_Integer>(theElements.size()),
				static_cast<Standard_Integer>(var.size()), file);

			WritePointsVariables(thePoints, file);

			WriteCellCenteredField(theElements, var, file);
		}
	}
}
