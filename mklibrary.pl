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
    dircopy("tftlib","/tmp/xmemtft") or die("Failed to copy library files: $!");

    # remove the font xml files

    system("rm /tmp/xmemtft/Font_*.xml");
}


#
# copy examples
#

sub copyExamples {
    
    print "Copying examples...\n";
    mkdir("/tmp/xmemtft/examples");
                
    dircopy("examples","/tmp/xmemtft/examples") or die("Failed to copy examples: $!");
    fcopy("globe64x64.bin","/tmp/xmemtft") or die("Failed to copy globe64x64.bin: $!");
}


#
# copy utility programs
#

sub copyUtilities {

    print("Copying utility files...\n");

    mkpath("/tmp/xmemtft/utility/bm2rgbi") or die("Failed to copy: $!");
    mkpath("/tmp/xmemtft/utility/fontconv") or die("Failed to copy: $!");
    mkpath("/tmp/xmemtft/utility/lzgfontconv") or die("Failed to copy: $!");
    mkpath("/tmp/xmemtft/utility/sendjpeg") or die("Failed to copy: $!");

    copysrc("../stm32plus/utils/bm2rgbi","/tmp/xmemtft/utility/bm2rgbi","bm2rgbi");
    copysrc("../stm32plus/utils/fonts","/tmp/xmemtft/utility/fontconv","FontConv");
    copysrc("../stm32plus/utils/fonts","/tmp/xmemtft/utility/lzgfontconv","LzgFontConv");

    fcopy("../stm32plus/utils/fonts/FontConv/bin/Release/FontConv.exe","/tmp/xmemtft/utility/fontconv")
	or die("Failed to copy: $!");
    
    fcopy("../stm32plus/utils/fonts/LzgFontConv/bin/Release/LzgFontConv.exe","/tmp/xmemtft/utility/lzgfontconv")
	or die("Failed to copy: $!");
    
    fcopy("../stm32plus/utils/bm2rgbi/bm2rgbi/bin/Release/bm2rgbi.exe","/tmp/xmemtft/utility/bm2rgbi")
	or die("Failed to copy: $!");
    
    fcopy("../stm32plus/utils/bm2rgbi/bm2rgbi/bin/Release/lzg.exe","/tmp/xmemtft/utility/bm2rgbi")
	or die("Failed to copy: $!");
    
    fcopy("examples/JpegSerial/SendJpeg/bin/Release/SendJpeg.exe","/tmp/xmemtft/utility/sendjpeg")
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
