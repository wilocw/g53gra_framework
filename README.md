# C++ Framework for Coursework and Demos
#### G53GRA Computer Graphics
#### Spring Semester 2016/17

The documentation of this framework is covered _in full_ in the provided
specification, available from
[Moodle](http://moodle.nottingham.ac.uk/mod/resource/view.php?id=2404290). Note
that the use of this framework is _optional_ and completely at your discretion,
however you may find it easier tofocus on applying the computer graphics theory
with all the windowing handled.

A software document reference for the framework classes is also available
[here](http://www.cs.nott.ac.uk/~psxwowa/framework/documentation).

## Overview
The framework is cross-platform and uses OpenGL, (free)GLUT and GLU. Prebuilt
and linked projects are available for use with Windows under Visual Studio and 
macOS under XCode, containing two folders. The first, ``Framework", which 
contains all the pre-written code for you to use with your project. It is highly
recommended that you do NOT edit any of the files in this project: you should
just include the header files where appropriate, e.g.:

```c++
#include "DisplayableObject.h"
#include "Animation.h"
```
The latter folder, named "Code", will contain your coursework code. Some example
code, demonstrating various techniques for graphics programming, is provided
using the framework. The main class that you should run will be `MyScene.cpp`.
There is an overriding method `Initialise()` where you should define all your
objects and add them to thescene. Note that you should not attempt to override
`Scene::Draw` if you are using this framework.

## Setting Up
It is **__strongly__** recommended you use `git` to clone the
repository to your desktop, so you can pull updates and demos directly. If you
do not have `git` installed, you can find details for download and
installation [here](https://git-scm.com/downloads) -- note: A32 lab
machines already have `git` installed.

Run a terminal, or command prompt, and navigate to an appropriate directory
location. If you are using a lab machine you will need to navigate to the H:
drive in `cmd` first.

```
> H:
> mkdir G53GRA & cd G53GRA
> git clone https://projects.cs.nott.ac.uk/psxwowa/g53gra_framework.git
```
You will now be prompted for your username and password. You should enter for
__IS login__ details -- this will allow you to `pull` from the repository. You
should see:
```
> git clone 
https://projects.cs.nott.ac.uk/psxwowa/g53gra_framework.git
Cloning into 'g53gra_framework'...
remote: Counting objects: 477, done.
remote: Compressing objects: 100% (282/282), done.
remote: Total 477 (delta 276), reused 348 (delta 181)
Receiving objects: 100% (477/477), 2.74 MiB | 2.61 MiB/s, done.
Resolving deltas: 100% (276/276), done.
Checking connectivity... done.
```
To check this was successful, `cd` into the new folder and check the `git
status`. If the status matches the below, you have cloned the project
successfully.

```
> cd g53gra_framework
> git status
On branch coursework
your branch is up-to-date with 'origin/coursework'.
nothing to commit, working directory clean
```

You can now check the project file, for Windows/Visual Studio users it should be
located in `./G53GRA.Framework/G53GRA.Framework.sln`

The XCode project (for macOS users) is found in 
`./G53GRA.Framework/G53GRA.Framework/G53GRA.Framework.xcodeproj`

The project should build and run without error, and you should see an OpenGL
context window open with a black background. This is a success, and everything
is set up properly.

Any changes you now make, while writing your coursework, can be added and
committed to your local coursework branch to maintain source control over your
coursework. 