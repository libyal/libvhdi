dnl Function to detect if libvhdi dependencies are available
AC_DEFUN([AX_LIBVHDI_CHECK_LOCAL],
 [dnl Check for internationalization functions in libvhdi/libvhdi_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

