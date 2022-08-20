#!/usr/bin/perl

# From:
# https://superuser.com/questions/598678/view-number-of-glyphs-in-a-given-font-for-linux
# with minor modifications

# NOTE(linux): You will need Perl and the `libfont-ttf-perl` package.

use strict;
use warnings;

use Font::TTF::Font;

unless (defined $ARGV[0]) {
    die <<'EOT';
glyphs_counter.pl <path_to_font_file>

Prints glyph count for each input TTF file.
EOT
}

foreach (@ARGV) {
    my $f = Font::TTF::Font->open($_) || die "Unable to open font file $_";
    my $num = $f->{'maxp'}{'numGlyphs'};
    printf "%s (glyph count: %d)\n", $_, $num;
    $f->release;
}
