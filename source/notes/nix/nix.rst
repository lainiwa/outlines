
===
Nix
===
* https://search.nixos.org/packages

.. include:: .deployments.rst
.. include:: .flakes.rst
.. include:: .direnv.rst
.. include:: .nixery.rst


Web resources
#############
* https://mynixos.com/nixpkgs/options/security.acme.defaults
* https://search.nixos.org/options?show=services.openssh.ports&query=services.openssh.ports&from=0&size=15&sort=alpha_asc&channel=unstable


https://nix.dev/tutorials/ad-hoc-developer-environments

a::

    nix-shell -p cowsay lolcat
    nix-shell --pure -p cowsay lolcat
    # can be nested

    # reproducibility
    nix-shell -p git --run "git --version" --pure -I nixpkgs=https://github.com/NixOS/nixpkgs/archive/2a601aafdc5605a5133a2ca506a34a3a73377247.tar.gz

    # after all
    nix-collect-garbage
