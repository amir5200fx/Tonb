#pragma once
#ifndef _Geo2dIO_CSV_Header
#define _Geo2dIO_CSV_Header

#include <Pnt2d.hxx>  

#include <vector>
#include <string>

namespace tnbLib
{
    /**
     * @class GeoIO_CSV
     * @brief A class to handle reading and writing CSV files containing 2D points.
     *
     * This class provides methods to read and write CSV files that store coordinates
     * of points along with optional comments. Comments are denoted by lines starting with '#'.
     *
     * @note This class assumes that each line in the CSV file (excluding comments) contains
     *       two comma-separated values representing the x and y coordinates of a point.
     *
     * @author [Amir Amir-Solaymani]
     * @date May 21, 2024
     */

    class Geo2dIO_CSV
    {
        /**
         * @brief Checks if a line is a comment.
         * @param line The line to check.
         * @return True if the line is a comment, false otherwise.
         */
        bool IsComment(const std::string& line);

        /**
         * @brief Parses a line into a Pnt2d object.
         * @param line The line to parse.
         * @return A Pnt2d object representing the coordinates.
         */
        Pnt2d ParseLine(const std::string& line);

    public:
        /**
         * @brief Reads a CSV file containing points and comments.
         * @param filename The name of the file to read.
         * @param comments A string to store the comments from the file.
         * @param coordinates A vector to store the points from the file.
         */
        TnbGeo_EXPORT void Read(const std::string& filename, std::string& comments, std::vector<Pnt2d>& coordinates);

        /**
         * @brief Writes points and comments to a CSV file.
         * @param filename The name of the file to write.
         * @param comments A string containing the comments to write.
         * @param coordinates A vector containing the points to write.
         */
        TnbGeo_EXPORT void Write(const std::string& filename, const std::string& comments, const std::vector<Pnt2d>& coordinates);
    };

}

#endif // _Geo2dIO_CSV_Header
