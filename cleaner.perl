#!/usr/bin/env perl
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    clean-git-track-histo.pl                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 12:39:54 by abarthel          #+#    #+#              #
#    Updated: 2019/06/24 12:40:40 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

use warnings;
use strict;
use 5.010;

open my $in, "<:encoding(utf8)", $ARGV[0] or die "$ARGV[0]: $!";
my @lines = <$in>;
close $in;

for my $line (@lines) {
#	printf ${line}; # To test your log file first !
	`bfg --delete-files ${line}` # Uncomment to delete your log
}
