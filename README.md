SESC_RRIP
=========

Re-reference interval prediction using SESC.
--------------------------------------------

IMPORTANT: I am not one of the creators of SESC, I just have the source hosted here so I can easily work on it with my partner for an architecture project.

Set-up:
  1. ```sudo apt-get install build-essential bison flex binutils git```
  2. If you want to make changes, fork my repo through GitHub.
  3. ```cd <where you want the source code to go>```
  4. Clone your fork. (```git clone <copy-paste link from top section of your fork's main page>```)

I have a Code directory in my home, so I cloned the project in Code.  For me it's like this:
```bash
cd ~/Code
git clone git@github.com:jship/SESC_RRIP.git
```

The next steps will assume your code was cloned to ~/Code/SESC_RRIP.

Steps to build:
```bash
cd ~/Desktop  # or wherever you want to build everything
mkdir sesc_build
cd sesc_build
../../Code/SESC_RRIP/configure  # using the parent directories is oddly mandatory
make
make testsim  # this is the simple test to see if everything is working
```