#!/usr/bin/perl -w

use strict;
use warnings;

use File::Copy::Recursive qw(dircopy fcopy fmove);
use File::Path;
use File::Find;
use Cwd;


die("Usage: mklibrary <version>")
    unless($#ARGV==0);

my $version=$ARGV[0];
print("Creating version ${version}...\n");

rmtree("/tmp/xmemtft");
mkdir("/tmp/xmemtft");


copyLibrary();
copyExamples();
copyUtilities();
copyMiscFiles();
createVersionStamp();
createZip();


#
# copy misc files
#

sub copyMiscFiles {

    print("Copying misc files...\n");

    fcopy("CHANGELOG.html","/tmp/xmemtft") or die("Failed to copy: $!");
}



#
# copy everything in tftlib
#

sub copyLibrary {

    print("Copying library files...\n");
    dircopy("lib","/tmp/xmemtft") or die("Failed to copy library files: $!");
		foreach my $dir (glob("/tmp/xmemtft/Release_* /tmp/xmemtft/Debug_*")) {
				rmtree($dir);
		}

    # remove the font xml files

    system("rm /tmp/xmemtft/Font_*.xml");
}


#
# copy examples
#

sub copyExamples {
    
    print "Copying examples...\n";
    mkdir("/tmp/xmemtft/examples");
                
    dircopy("examples/arduinoIDE","/tmp/xmemtft/examples") or die("Failed to copy examples: $!");
}


#
# copy utility programs
#

sub copyUtilities {

    print("Copying utility files...\n");

    mkpath("/tmp/xmemtft/utility") or die("Failed to copy: $!");

    copysrc(".","/tmp/xmemtft/utility","utility");

    fcopy("utility/fonts/FontConv/bin/Release/FontConv.exe","/tmp/xmemtft/utility")
	or die("Failed to copy: $!");
    
    fcopy("utility/fonts/LzgFontConv/bin/Release/LzgFontConv.exe","/tmp/xmemtft/utility")
	or die("Failed to copy: $!");
    
    fcopy("utility/bm2rgbi/bm2rgbi/bin/Release/bm2rgbi.exe","/tmp/xmemtft/utility")
	or die("Failed to copy: $!");
    
    fcopy("utility/bm2rgbi/bm2rgbi/bin/Release/lzg.exe","/tmp/xmemtft/utility")
	or die("Failed to copy: $!");
    
    fcopy("examples/ArduinoIDE/AllPanels/JpegSerial/SendJpeg/bin/Release/SendJpeg.exe","/tmp/xmemtft/utility")
	or die("Failed to copy: $!");

}


#
# copy a visual studio source dir and remove bins
#

sub copysrc {

    my($srcroot,$destroot,$srcdirname)=@_;
    my @removals=();

    dircopy("${srcroot}/${srcdirname}","${destroot}/src") or die("Failed to copy ${srcroot}/${srcdirname}");

    File::Find::find(
        sub {
            my $file = $_;

            if( -d $file && ($file =~ /^bin$/ || $file =~ /^obj$/)) {
								push(@removals,$File::Find::name);
						}
				}, "${destroot}/src");


    foreach my $dir (@removals) {
				print "Removing ${dir}\n";
				rmtree($dir) or die("Cannot remove $dir");
    }
}


#
# Create the version marker
#

sub createVersionStamp {

    print "Creating version file...\n";

    open FH,">/tmp/xmemtft/VERSION";
    print FH "${version}\n";
    close FH;
}


#
# zip it up
#

sub createZip {

    print "Creating zip archive...\n";
         
    my $mydir=getcwd();
    my $filename="xmemtft-${version}.zip";
    chdir("/tmp");
    system("zip -9r ${filename} xmemtft");
    chdir($mydir);
    
    unlink($filename);
    fmove("/tmp/$filename",$filename) or die("Failed to move zip archive: $!");
}
