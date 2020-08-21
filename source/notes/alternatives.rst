
============
Alternatives
============

Different software I ever considered

Legend:

* ✔ means I consider something to be a positive thing
* ✖ means I consider something misfortunate
* ★ means this is the thing I've currently settled with


Zsh plugin manager
##################

I've tried a buch of zsh plugin managers (something like `antigen → antibody → zinit → antibody → zinit → zpm`).

For most of the time I've used to stick with `zinit`, using it as a sort of ports manager. It can fetch binaries along with completions, man pages etc. It is very complex though, being something of a "systemd of the zsh plugins world".

I've switched to `zmp` later, as it is extrimely simple, and you can make most of the `zinit`'s functionality (that I've used) with simple wget/curl requests.

* :gh:`zinit <zdharma/zinit>` [44k loc C]
    - ✔ Versatile tool, has it's own ports system, thus letting you install non-plugins along with completions and keybindings.
    - ✔ Somewhat decent `README.md` documentation (although sometimes it lags behind the actual functionality)
    - ✖ Complex
* :gh:`sheldon <rossmacarthur/sheldon>` [2k loc Rust]
    - ✔ ??
    - ✖ Not very popular.
    - ✖ Rust language. Have to grab a binary.
* :gh:`antibody <getantibody/antibody>` [0.9k loc Go]
    - ✔ Simple
    - ✖ No ability to tightly integrate zsh settings with code installing non-plugins.
    - ✖ Go language. Have to grab a binary.
* ★ :gh:`zpm <zpm-zsh/zpm>` [650 loc Zsh]
    - ✔ Simple
    - ✔ Pure ZSH


Dotfiles manager/bootstrapper
#############################
* :gh:`chezmoi <twpayne/chezmoi>` [13.9k loc Go]
* :gh:`stow <aspiers/stow>` [2k loc Perl]
* :gh:`yadm <TheLocehiliosan/yadm>` [1.5 loc Bash]
* :gh:`homeshick <andsens/homeshick>` [1.5k loc Bash]
* :gh:`rcm <thoughtbot/rcm>` [1k loc Shell (?)]
* ★ :gh:`dotbot <anishathalye/dotbot>` [0.7k loc Python]


Window Manager
##############
* ★ :gh:`i3 <i3/i3>` [24k loc C]
    - ✔ Has a drop-in Wayland-compatible replacement (:gh:`sway <swaywm/sway>`). X11 will get:gh: sooner or aer.
    - ✔ Good docs.
    - ✖ Complex. Sway is even bigger.
    - ✖ i3status :gh:`depends <i3/i3status/pull/43>` pulseaudio lbary
* :gh:`herbstluftwm <herbstluftwm/herbstluftwm>` [11k loc C++]
* :gh:`bspwm <baskerville/bspwm>` [10.6k loc C]
    - ✖ Requires :gh:`sxhkd <baskerville/sxhkd>` (additional 3.5k loc C)
* :gh:`spectrwm <conformal/spectrwm>` [11.7 loc C]
* `dwm <https://dwm.suckless.org/>`_ [1.8k loc C]
    - ✔ Very (overly) simple.
    - ✖ Patching is PITA.


Picker
######

Seems like only `fzf` has decent environment & tools built around it.

* ★ :gh:`fzf <junegunn/fzf>` [10k loc Go]
    - ✔ Many tools integrating this (and only this).
    - ✖ Very complex for such simple task
    - ✖ Go language. Have to grab a binary.
* :gh:`fzy <jhawthorn/fzy>` [2k loc C]
    - ✔ Has some tools integrating this.
    - ✖ Still complex
* :gh:`pick <mptre/pick>` [1.1k loc C]
    - ✖ No tools integrated
* :gh:`slmenu <joshaw/slmenu>` [0.6k loc C]
    - ✔ Somewhat simple
    - ✖ No tools integrated
    - ✖ Not fuzzy


Terminal emulator
#################

These two emulator seem to be most viable. `St` is better but source-code-as-a-config doesn't fit my workflow.

* ★ `urxvt <https://wiki.archlinux.org/index.php/rxvt-unicode>`_ [40k loc C]
    - ✔ Extendable with Perl plugins
    - ✖ Complex. Relies on Perl
* `st <https://wiki.archlinux.org/index.php/St>`_ [4k loc C]
    - ✔ simplest out there
    - ✔ correct. Passes `UTF-8 test <https://www.cl.cam.ac.uk/~mgk25/ucs/examples/UTF-8-demo.txt>`_
    - ✖ Having terminal multiplexer is essential.
    - ✖ Settings in source code.


Shell
#####
* `bash <https://www.gnu.org/software/bash/>`_ [107k loc C]
* ★ `zsh <http://www.zsh.org/>`_ [102k loc C]
* :gh:`mksh <MirBSD/mksh>` [19k loc C]
* :gh:`rc <rakitzis/rc>` [6.5k loc C]


File Manager
############

The one thing I think file manager is useful for is picking files based on preview of their contents. For now only `ranger` has this functionality.

* ★ :gh:`ranger <ranger/ranger>` [12.8k loc Python]
* :gh:`lf <gokcehan/lf>` [7k loc Go]
* ★ :gh:`nnn <jarun/nnn>` [3.8k loc C]
* :gh:`fff <dylanaraps/fff>` [674 loc Bash]


Package Manager
###############
* ★ :gh:`guix <guix-mirror/guix>` [~60k loc Scheme]
* ★ :gh:`nix <NixOS/nix>` [~37 loc C++]


Grep through code
#################
* ★ :gh:`ag <ggreer/the_silver_searcher>` [3.9 loc C]
* :gh:`rg <BurntSushi/ripgrep>` [21k loc Rust]

Browser Extensions
##################
* ★ :gh:`uBlock <gorhill/uBlock>` [~48k loc JavaScript]

Screenshoters
#############
* :gh:`imagemagick <ImageMagick/ImageMagick>` [334k loc C]
* :gh:`flameshot <lupoDharkael/flameshot>` [7.5k loc C++]
* ★ :gh:`maim <naelstrof/maim>` [2.4k loc C++]
* :gh:`scrot <dreamer/scrot>` [1.8k loc C]

Wallpaper Setters
#################

Web Browsers
############
* `firefox <http://localhost>`_ []
* :gh:`brave <brave/brave-browser>` []
* ★ `chromium <http://localhost>`_ []
* :gh:`qutebrowser <qutebrowser/qutebrowser>` []
* `lynx <http://localhost>`_ []

Web Browsers
############
* :gh:`bitwarden <bitwarden/browser>` []
* :gh:`KeePassXC <keepassxreboot/keepassxc>` []
