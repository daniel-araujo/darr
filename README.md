# darr

A dynamically sized array library for C.


## Table of contents

1. Introduction
2. Reporting Bugs
3. License


## 1. Introduction

darr is a C library that abstracts most of the arithmetic that is done when
attempting to emulate a resizable array with malloc and realloc. The motivation
for writing this tiny library is to put an end to that repetitive and error
prone memory allocation dance. It's as efficient as one would achieve when
writing manually.


## 2. Reporting bugs

If you encounter a bug, please open an issue on GitHub:

	https://github.com/daniel-araujo/darr/issues


## 3. License

This program is free software: you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
