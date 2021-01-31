%define name cmake_sample
%define version 1.0.2

Name: %{name}
Version: %{version}
Release: 1%{?dist}
Summary: cmake sample program

Group: Development/Tools
License: GPL
URL: http://www.example.com/%{name}-%{version}
Source0: http://www.example.com/download/%{name}-%{version}.tar.gz

BuildRequires: cmake
Requires: bash

%description
cmake_sample

%prep
%setup -q -n %{name}-%{version}

%build
rm -rf _build
mkdir -p _build
cd _build
%cmake ..
make %{?_smp_mflags}

%install
cd _build
make install DESTDIR=%{buildroot}

%files
%doc README
%{_bindir}/*
%{_libdir}/*
%{_includedir}/*

