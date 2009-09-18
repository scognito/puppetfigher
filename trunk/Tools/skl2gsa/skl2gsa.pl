#!/usr/bin/perl
use File::Basename;

my $version;
my $canvaswidth;
my $canvasheight;
my $canvasbg;
my $framedelay;
my $maxbones;
my $maxframes;
my $frame;
my @frames;
my %id_map = ();

sub trim($)
{
	my $str = shift;
	$str =~ s/^\s+//;
	$str =~ s/\s+$//;
	return $str;
}

sub makebonename($)
{
	my $bone = shift;
	my $bonename = %{$frames[1]}->{"bones"}->{$bone}->{"image"};
	$bonename =~ s/\.[^\.]+$//;
	$bonename =~ s/[\.\\]//g;
	$bonename = "Bone$bone$bonename";
	return $bonename;
}

sub makeboneimage($)
{
	my $bone = shift;
	my $bonename = %{$frames[1]}->{"bones"}->{$bone}->{"image"};
	$bonename =~ s/\.[^\.]*$//;
	$bonename =~ s/[\.\\]//g;
	return $bonename;
}
sub parseFile($)
{
	my($fname) = @_;
	my @frames;
	
	$maxbones  = 0;
	$maxframes = 0;
	$frame = -1;

	open FILE, $fname;
	
	$version = trim(<FILE>);
	$canvaswidth = trim(<FILE>);
	$canvasheight = trim(<FILE>);
	$canvasbg = trim(<FILE>);
	$framedelay = trim(<FILE>);

	my $id = 0;
	
	while(1) {
		my $div = trim(<FILE>);
		if($div eq "--------") {
			my $bonenum = int(trim(<FILE>)) - 1000;
			#print "Bone $bonenum\n";
			my $parent		= trim(<FILE>);
			my $angle			= trim(<FILE>);
			my $length		= trim(<FILE>);
			my $image			= trim(<FILE>);
			my $hscale		= trim(<FILE>);
			my $vscale		= trim(<FILE>);
			my $imgangleoffset = trim(<FILE>);
			my $imgposition = trim(<FILE>);
			my $depth			= trim(<FILE>);
			my $alpha			= trim(<FILE>);
			my $color			= trim(<FILE>);
			
			$id_map{$bonenum} = $id;
			$id++;

			if($parent =~ /^\d+\.\d+$/) {
				$parent = int($parent) - 1000;
			}
			$angle = -$angle;

			%{%{$frames[$frame]}->{"bones"}}->{$bonenum} =
				{
					"parent"		=> $parent,
					"angle"			=> $angle,
					"length"		=> $length,
					"image"			=> $image,
					"hscale"		=> $hscale,
					"vscale"		=> $vscale,
					"imgangleoffset" => $imgangleoffset,
					"imgposition" => $imgposition,
					"depth"			=> $depth,
					"alpha"			=> $alpha,
					"color"			=> $color
				};  
			if($frame == 1) {
				$maxbones++;
			}
		} elsif ($div eq "********") {
		  $frame++;
		  #print "Frame $frame\n";
		  $frames[$frame] =
				{
					"originx" => trim(<FILE>),
					"originy" => trim(<FILE>)
				};
		} else {
			last;
		}
	}
	$maxframes = $frame+1;

	close FILE;
	
	return @frames;
}

sub printUseage(){
	print "Useage: perl skl2gsa.pl <base skl file> [<anim skl file> ... <anim skl file> ]\n";
	print "     <base skl file> - the base skeleton file w/out any animation (single frame)\n";
	print "     <anim skl file> - the base skeleton animated e.g. Walk\n\n";
}

# Read in skl file

if(@ARGV == 0)
{
   printUseage();
   exit;
}

#ARGV[0] is the generic skeleton definition file
@frames = parseFile($ARGV[0]);

# Output code
my $bone_count = keys %{%{$frames[0]}->{"bones"}};

print "skeleton\n";
print "$bone_count\n";
my $j = 0;

foreach my $bone (sort keys %{%{$frames[0]}->{"bones"}}) {
  my $bonenum = $id_map{$bone};
  my $parent =%{$frames[0]}->{"bones"}->{$bone}->{"parent"};
  my $angle = %{$frames[0]}->{"bones"}->{$bone}->{"angle"};
  my $length = %{$frames[0]}->{"bones"}->{$bone}->{"length"};
  if($parent == -1000) {
    $parent = "-1";
  } 
  else
  {
     $parent = $id_map{$parent};
  }

  $j++;
  print "$bonenum $parent $angle $length\n";
}

my $originx = 0;
my $originy = 0;
  
print "animation\n";
print "idle 0 $maxframes\n";

my $i = 0;
foreach my $frame (@frames) {
my $originx = %{$frame}->{"originx"};
my $originy = %{$frame}->{"originy"};
	print "$originx $originy $bone_count 0.0\n";
	foreach my $bone (sort keys %{%{$frame}->{"bones"}}) {
	  my $angle = %{$frame}->{"bones"}->{$bone}->{"angle"};
	  
	  print "$i $angle\n";
	  $i++;
	}
	
}

my $num_args = @ARGV;
my $k=1;

while($k < $num_args)
{
	@frames = parseFile($ARGV[$k]);
	print "animation\n";
	my ( $name, $path, $suffix ) = fileparse( $ARGV[$k], qr/\.[^.]*/ );
	print "$name $k $maxframes\n";

	my $i = 0;
	foreach my $frame (@frames) {
		$i=0;
		my $originx = %{$frame}->{"originx"};
		my $originy = %{$frame}->{"originy"};
		
		print "$originx $originy $bone_count $framedelay\n";
		
		foreach my $bone (sort keys %{%{$frame}->{"bones"}}) {
		  my $angle = %{$frame}->{"bones"}->{$bone}->{"angle"};
		  
		  print "$i $angle\n";
		  $i++;
		}
		
	}
	$k++;
}
	print "\n";
