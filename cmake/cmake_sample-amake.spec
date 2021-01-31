%define name cmake_sample
%define version 1.0.2
%define _configure ../configure

%global mingw 0

%if %{mingw}
%define host x86_64-w64-mingw32
%else
%define host %{_host}
%endif

Name: %{name}
Version: %{version}
Release: 1%{?dist}
Summary: cmake sample program

Group: Development/Tools
License: GPL
URL: http://www.example.com/%{name}-%{version}
Source0: http://www.example.com/download/%{name}-%{version}.tar.gz

%if %{mingw}
BuildArch: noarch
%endif

BuildRequires: make gcc
#Requires: 
#BuildArch: noarch

%description
cmake_sample

%prep
%setup -q -n %{name}-%{version}

%build
mkdir -p _build
cd _build
sh ../configure \
	--host=%{host} \
	--build=%{_build} \
        --program-prefix=%{?_program_prefix} \
        --disable-dependency-tracking \
        --prefix=%{_prefix} \
        --exec-prefix=%{_exec_prefix} \
        --bindir=%{_bindir} \
        --sbindir=%{_sbindir} \
        --sysconfdir=%{_sysconfdir} \
        --datadir=%{_datadir} \
        --includedir=%{_includedir} \
        --libdir=%{_libdir} \
        --libexecdir=%{_libexecdir} \
        --localstatedir=%{_localstatedir} \
        --sharedstatedir=%{_sharedstatedir} \
        --mandir=%{_mandir} \
        --infodir=%{_infodir}

make %{?_smp_mflags}
cd ..

%install
cd _build
make install DESTDIR=%{buildroot}
rm -f %{buildroot}/usr/share/CMakeLists.txt
rm -f %{buildroot}/usr/share/build.sh
cd ..

%clean

%files
%doc README
%{_bindir}/*
%{_libdir}/*
%{_includedir}/*

