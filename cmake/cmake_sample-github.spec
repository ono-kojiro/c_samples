%define name cmake_sample
%define version 1.0.3

%global use_master 0
%global use_tag    1
%global use_commit 0

%global commit 285dbc6a280c301d88460f4f88cef38ff7576225
%global shortcommit %(c=%{commit}; echo ${c:0:7})

%global gittag %{version}

Name: %{name}
Version: %{version}
Release: 1%{?dist}
Summary: cmake sample program

Group: Development/Tools
License: GPL

%if %{use_master}
Source0:  https://github.com/k02160/%{name}/archive/master.tar.gz
%endif

%if %{use_tag}
Source0:  https://github.com/k02160/%{name}/archive/%{gittag}.tar.gz
%endif

%if %{use_commit}
Source0:  https://github.com/k02160/%{name}/archive/%{commit}/%{name}-%{shortcommit}.tar.gz
%endif


BuildRequires: cmake check check-devel
Requires: bash

%description
cmake_sample

%prep
%if %{use_master}
%setup -n %{name}-master
%endif

%if %{use_tag}
%setup -n %{name}-%{gittag}
%endif

%if %{use_commit}
%autosetup -n %{name}-%{commit}
%endif


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

