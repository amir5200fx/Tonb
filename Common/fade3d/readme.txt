Fade3D, v0.99beta, October 29th, 2017
---------------------------------------

Welcome to the Fade3D Library!

NOTE: Fade3D exists since several years but has gone public only recently. Please
report your impressions of Fade3D. Any feedback is appreciated.  


 Geom Software
 Bernhard Kornberger
 C++ Freelancer
 bkorn@geom.at


If you use Fade3D under the free of charge student license or evaluation license
please put a link to Fade on your project website.


The present download contains all library versions for
 
.) Windows (VS2008, VS2010, VS2012, VS2013, VS2015, VS2017) 
.) Linux on PC (gcc)
.) Apple (clang)



Linux and Apple users: 
----------------------

cd examples 
Important: Select your DISTRO in the Makefile (Apple, Ubuntu, CentOS, ...) 
$> make
$> ./allExamples3D

Windows users: 
--------------

Open a solution file 

examples/vs20xx_exampleProject/examples.sln  


For maximum performance compile in Release mode. Then open a command line 
window (cmd.exe), change to fadeRelease/x64 (or fadeRelease/Win32) and run 
the executable there. 


Directories
===========

.) include_fade3d
Header files  

.) x64 (and Win32)
Contains the *.dll and *.lib files for 64-bit (and 32-bit) Windows and further 
this is the target directory for the executables of the demo projects.

.) lib_${DISTRO}_${ARCHITECTURE}
The shared libraries (*.so) for Linux and Apple developers. The libraries work 
for a wide range of Linux distributions. Commercial users who need support for 
a certain additional Linux distribution: Please get in contact with the author. 

.) examples
Source code of all examples

.) doc
PDF Documentation




Student license
===============

Fade3D is free of charge for personal non-commercial scientific research. But we 
ask you to put a link to Fade3D on your research homepage or project page and to 
cite Fade2D in scientific publications using it. Fade is not free software. Do
not integrate it in a free software project without explicit permission.


Commercial license
==================

All other applications, including commercial in-house usage, require a commercial 
license which has the advantage of maintenance, error corrections and personal 
support.

Commercial Licenses will be available when Fade3D leaves the beta stage. If you
are willing to be a commercial beta tester you can get Fade3D at a reduced
price. 





Author: Geom e.U., Graz / Austria 
Bernhard Kornberger, bkorn@geom.at
C++-Freelancer, http://www.geom.at


In no case can Geom Graz/Austria be made responsible for damages of any kind that 
arise in connection with the use or non-usability of the software or information 
provided on our internet pages. If you can't accept these terms, you are not 
allowed to use our software. Using Fade for military research and applications 
is not accepted.


3rd party libraries
-------------------

The Fade 2D library uses the GNU Multiple Precision Arithmetic Library (see 
http://gmplib.org/ for details and the source code), released under the GNU 
Lesser General Public License (https://www.gnu.org/copyleft/lesser.html).



