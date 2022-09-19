#pragma once
#ifndef _Burkardt_Header
#define _Burkardt_Header

#include <string>
# include <cmath>
# include <cstdlib>
# include <cstring>
# include <ctime>
# include <fstream>
# include <iomanip>
# include <iostream>

using namespace std;

char ch_cap(char ch);
bool ch_eqi(char ch1, char ch2);
int ch_to_digit(char ch);
int file_column_count(string filename);
int file_row_count(string input_filename);
int i4_max(int i1, int i2);
int i4_min(int i1, int i2);
int i4_modp(int i, int j);
int i4_wrap(int ival, int ilo, int ihi);
bool line_exp_is_degenerate_nd(int dim_num, double p1[], double p2[]);
double *line_exp_perp_2d(double p1[2], double p2[2], double p3[2], bool *flag);
void line_exp2imp_2d(double p1[2], double p2[2], double *a, double *b,
	double *c);
bool line_imp_is_degenerate_2d(double a, double b, double c);
void lines_exp_int_2d(double p1[2], double p2[2], double p3[2], double p4[2],
	int *ival, double p[2]);
void lines_imp_int_2d(double a1, double b1, double c1, double a2, double b2,
	double c2, int *ival, double p[2]);
double r8_abs(double x);
double r8_acos(double c);
double r8_huge();
double r8_max(double x, double y);
double r8_min(double x, double y);
double *r8mat_data_read(string input_filename, int m, int n);
void r8mat_header_read(string input_filename, int &m, int &n);
double *r8mat_inverse_2d(double a[]);
int r8mat_solve(int n, int rhs_num, double a[]);
void r8mat_transpose_print(int m, int n, double a[], string title);
void r8mat_transpose_print_some(int m, int n, double a[], int ilo, int jlo,
	int ihi, int jhi, string title);
void r8vec_copy(int n, double a1[], double a2[]);
bool r8vec_eq(int n, double a1[], double a2[]);
double r8vec_norm(int dim_num, double x[]);
void r8vec_print(int n, double a[], string title);
int s_len_trim(string s);
double s_to_r8(string s, int *lchar, bool *error);
bool s_to_r8vec(string s, int n, double rvec[]);
int s_word_count(string s);
void timestamp();
void triangle_angles_2d(double t[2 * 3], double angle[3]);
double triangle_area_2d(double t[2 * 3]);
double *triangle_centroid_2d(double t[2 * 3]);
void triangle_circumcircle_2d(double t[2 * 3], double *r, double pc[2]);
bool triangle_contains_point_2d(double t[2 * 3], double p[2]);
double *triangle_edge_length_2d(double t[2 * 3]);
void triangle_incircle_2d(double t[2 * 3], double pc[2], double *r);
int triangle_orientation_2d(double t[2 * 3]);
void triangle_orthocenter_2d(double t[2 * 3], double p[2], bool *flag);
double triangle_quality_2d(double t[2 * 3]);



#endif // !_Burkardt_Header