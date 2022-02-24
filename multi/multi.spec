Name: multi
Version: 0.0.1
Release: 1%{?dist}
Summary: multi

Group:	 Applications/Internet	
License: GPL
URL:	 http://example.com/
Source0: https://example.com/%{name}/%{name}-%{version}.tar.gz
BuildRoot:	%(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

%description
multi

%prep

%build

%install
rm -rf %{buildroot}
%make_install -C ../..

%clean

%files
%defattr(-,root,root,-)
%{_bindir}/mystaticapp
%{_bindir}/mysharedapp
%{_includedir}/mysharedlib.h                   
%{_includedir}/mystaticlib.h
%{_libdir}/libmysharedlib.a
%{_libdir}/libmysharedlib.la
%{_libdir}/libmysharedlib.so
%{_libdir}/libmysharedlib.so.0
%{_libdir}/libmysharedlib.so.0.0.0
%{_libdir}/libmystaticlib.a

%changelog

