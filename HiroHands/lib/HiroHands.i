%include <python/file.i>
%include <carrays.i>
%array_class(float, fAray);

%module HiroHands
%{
#include "HiroHands.hpp"
%}

%include "HiroHands.hpp"
%include "Logger.hpp"
