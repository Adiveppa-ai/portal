#!/home/pin/opt/portal/Thirdparty/perl-5.38.2/bin/perl

$cmd = "sqlplus integrate\@QA10/integrate \@insertWIRELESS_SAMPLE.sql";
system($cmd);

exit 0;
