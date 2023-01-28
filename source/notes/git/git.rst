===
Git
===

Sources:

* Cheat Sheets
    - `Oh Shit Git <https://ohshitgit.com/>`_
    - `Git and Github Cheatsheet <https://dev.to/zinox9/git-github-cheatsheet-22ok>`_
    - https://bitbucket.org/BitPusher16/dotfiles/src/master/refs/git/git_examples.sh
    - https://github.com/k88hudson/git-flight-rules
    - https://danielkummer.github.io/git-flow-cheatsheet/
    - https://github.com/nikitavoloboev/knowledge/blob/master/programming/version-control/git.md
    - https://git.wiki.kernel.org/index.php/Interfaces,_frontends,_and_tools
    - https://dev.to/henryong92/yet-another-git-cheatsheet-4gjk
* Exercises
    - https://ohmygit.org/
    - https://learngitbranching.js.org/
    - https://gitexercises.fracz.com
* Config
    - `Limiting Upstream Tracking <https://utcc.utoronto.ca/~cks/space/blog/programming/GitUpstreamLimitedTracking>`_
* Intros
    - `Visual Git <https://marklodato.github.io/visual-git-guide/index-en.html>`_
    - `Git for Computer Scientists <https://eagain.net/articles/git-for-computer-scientists/>`_
    - `The Wave/Particle Duality of Git Commits <https://www.thirtythreeforty.net/posts/2020/01/the-wave-particle-duality-of-git-commits/>`_
    - `Think Like a Git <http://think-like-a-git.net>`_
    - `How to explain git in simple words? <https://xosh.org/explain-git-in-simple-words/>`_
* Fundamentals
    - https://habr.com/ru/company/badoo/blog/163853/
    - https://www.kenneth-truyers.net/2016/10/13/git-nosql-database/
* Alternatives
    - https://monorepo.tools/
* Others, used:
* `GitLab Tutorial <http://dept.cs.williams.edu/~freund/cs434/GitLab.html>`_
* https://dev.to/lydiahallie/cs-visualized-useful-git-commands-37p1
* https://docs.gitlab.com/ee/topics/git/numerous_undo_possibilities_in_git/
* https://git-scm.com/book/ru/v2/Ветвление-в-Git-Основы-ветвления-и-слияния
* https://githowto.com/ru
* https://githowto.com/ru/setup
* https://habr.com/ru/post/512490/
* https://www.atlassian.com/git/tutorials/using-branches/merge-strategy
* Learning Git from Novice to Expert: https://news.ycombinator.com/item?id=23149700
* https://symflower.com/en/company/blog/2021/git-autofixup/
* https://github.blog/tag/git/


.. image:: imgs/rant.png
  :width: 49%
  :target: https://youtu.be/4XpnKHJAok8


`References make commits reachable <http://think-like-a-git.net/sections/experimenting-with-git.html>`_


Snippets
########

.. code-block:: sh

    git pull == git fetch && git merge/rebase

    git branch -f master HEAD~ == git switch master && git reset --soft HEAD~

    git clone -b mybranch --single-branch git://sub.domain.com/repo.git

    git pull --ff-only && git push

    git push -u origin master

    # Fix last commit message
    git commit --amend -m "fixed message of last commit"

    # Change last commit content
    vim ...
    git add ...
    git commit --amend --no-edit

    # Modify specific commit
    git rebase --interactive 'bbc643cd^'  # -> `e`

    # Clone github wiki (e.g. wiki of https://github.com/swaywm/sway/wiki)
    git clone https://github.com/swaywm/sway.wiki

    # Accept pull request
    curl -sL https://github.com/nodejs/node/pull/37544.patch | git am

    # Mirror repo to another server
    git clone --bare https://github.com/exampleuser/old-repository.git
    cd old-repository.git
    git push --mirror https://github.com/exampleuser/new-repository.git

    # Delete remote branch
    git push origin --delete old-branch

.. include:: .git_diff.rst
.. include:: .git_tag.rst
.. include:: .git_checkout.rst
.. include:: .git_reset.rst
.. include:: .git_revert.rst
.. include:: .git_rebase_cherry_pick.rst
.. include:: .git_merge.rst
.. include:: .git_stash.rst
.. include:: .git_blame_bisect.rst
.. include:: .git_conflicts.rst
.. include:: .git_stacked.rst
.. include:: .git_logs.rst
.. include:: .git_submodule_subtree.rst
.. include:: .git_tig.rst
.. include:: .git_worktree.rst
.. include:: .git_notes.rst

PGP
###
* https://www.kernel.org/doc/html/latest/process/maintainer-pgp-guide.html
* https://people.kernel.org/monsieuricon/what-does-a-pgp-signature-on-a-git-commit-prove
* https://people.kernel.org/monsieuricon/signed-git-pushes
* https://github.com/pstadler/keybase-gpg-github
* https://github.com/jayphelps/git-blame-someone-else
* https://github.com/lfit/itpol/blob/master/protecting-code-integrity.md

.. code-block:: sh

    # Show info on tag
    git cat-file -p v5.8-rc7
        #--> object 92ed30...
        #--> type commit
        #--> ...
    # Show info on tagged commit
    git cat-file -p 92ed30

    # Verify tag
    git verify-tag    v5.8-rc7
    git verify-commit v5.8-rc7

Clean
#####

.. code-block:: sh

    # Clean untracked files (like a `rm *`)
    git clean -f|--force
    # Recursive clean of untracked files (like a `rm -r *`)
    git clean -fd

    #
    git clean ... [-n|--dry-run]

Reflog
######

Ignoring
########
* https://git-scm.com/docs/gitignore

``.gitignore``
==============
Shared gitignore.

``.git/info/exclude``
=====================
Personal (local) gitignore.

Examples
########

Create and use a local remote
=============================

.. code-block:: sh

    git init --bare ~/projects/remotes/test.git
    mkcd ~/projects/test && git init
    git remote add origin ~/projects/remotes/test.git
    git push origin master
    git clone ~/projects/remotes/test.git test1

Sync a fork
===========

.. code-block:: sh

    git remote add upstream https://github.com/larkery/zsh-histdb.git
    # git remote -v
    git fetch upstream
    # git branch --all
    # <merge/rebase here>

Unfuckup the master branch
==========================

.. code-block:: sh

    # Get the lastest state of origin
    git fetch origin
    git checkout master
    git reset --hard origin/master
    # Delete untracked
    git clean -fd

Practices
#########
* The Problem with Git Flow: https://news.ycombinator.com/item?id=23622071
* `Git Standards <https://blog.carlmjohnson.net/post/2018/git-gud/>`_
* https://martinfowler.com/articles/branching-patterns.html
* https://habr.com/ru/post/519314/
* `When it comes to git history, less is more <https://brennan.io/2021/06/15/git-less-is-more/>`_
* `Things I wish Git had: Commit groups <https://blog.danieljanus.pl/2021/07/01/commit-groups/>`_
* `Trunk Based Development <https://trunkbaseddevelopment.com/>`_
* https://medium.com/@kentbeck_7670/test-commit-revert-870bbd756864

Merge vs Rebase
===============
* `For rebase + merge --no-ff <https://gist.github.com/zerowidth/4684495>`__
* `Comparison with conclusion <https://blog.sourcetreeapp.com/2012/08/21/merge-or-rebase/>`__
* `A Rebase Workflow for Git  <https://randyfay.com/comment/1093>`_
* `Git team workflows: merge or rebase? <https://www.atlassian.com/git/articles/git-team-workflows-merge-or-rebase>`__
* `Merging vs. Rebasing <https://www.atlassian.com/git/tutorials/merging-vs-rebasing>`_

Commit Messages
===============
* https://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html
* https://www.conventionalcommits.org
* https://udacity.github.io/git-styleguide/index.html


Filer-repo
##########
* `How can I clang-format my WHOLE git history? <https://stackoverflow.com/questions/58042532/how-can-i-clang-format-my-whole-git-history>`_
* `How to Use Git-Filter-Repo to Remove Files From Your Git Repository <https://improveandrepeat.com/2021/06/how-to-use-git-filter-repo-to-remove-files-from-your-git-repository/>`_
* `Reduce repository size <https://docs.gitlab.com/ee/user/project/repository/reducing_the_repo_size_using_git.html#purge-files-from-repository-history>`_
* `Cheat Sheet: Conversion of Examples from the filter-branch manpage <https://github.com/newren/git-filter-repo/blob/main/Documentation/converting-from-filter-branch.md#cheat-sheet-conversion-of-examples-from-the-filter-branch-manpage>`_
* https://blog.gitguardian.com/rewriting-git-history-cheatsheet/
* https://marcofranssen.nl/remove-files-from-git-history-using-git-filter-repo
* https://stackoverflow.com/questions/61420660/how-to-use-git-filter-repo-to-merge-one-repo-as-subdirectory-into-another
* https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/removing-sensitive-data-from-a-repository

.. code-block:: sh

    # Remove file(s) from the repo
    # without `--invert-paths` it will unuke everything but the `Templates/`
    git filter-repo --invert-paths --path Templates/
    git push origin --tags

    # Remove big files
    git filter-repo --strip-blobs-bigger-than 10M
    git push origin --force 'refs/heads/*'    # Overwrite all branches
    git push origin --force 'refs/tags/*'     # Remove large files from tagged releases
    git push origin --force 'refs/replace/*'  # Prevent dead links (created by git filter-repo)

    # Change one word in all commits
    FILTER_BRANCH_SQUELCH_WARNING=1 \
    git filter-branch -f --tree-filter "sed -e 's#shit#flower#g' -i *.txt" 685966d6..HEAD


Extensions
##########

Git DVC
=======
* https://dvc.org/doc
* too bad https://florianwinkelbauer.com/posts/2020-02-08-git-with-chunks/

::

    mkcd tstdvc

    git init
    dvc init
    git status
    git commit -m "Initialize DVC"

    dvc remote add -d myremote /tmp/dvcstore

Git Bug
=======
* https://github.com/MichaelMure/git-bug

::

    git bug user create
    git bug add
    git bug ls
    git bug push
    git bug termui
    git bug webui

Internals
#########
* `Storing files in .git <https://www.arp242.net/dot-git.html>`_
* `A Random Walk Through Git <https://bakkenbaeck.github.io/a-random-walk-through-git/>`_
* `Git from the Bottom Up <https://jwiegley.github.io/git-from-the-bottom-up/>`_
* `Some of git internals <https://yurichev.com/news/20201220_git/>`_
* https://articles.foletta.org/post/git-under-the-hood/
* https://github.blog/2022-09-13-scaling-gits-garbage-collection/
* https://github.blog/2022-08-29-gits-database-internals-i-packed-object-store/
* https://codewords.recurse.com/issues/two/git-from-the-inside-out

.. code-block:: sh

    # A todo inside .git directory
    vim .git/todo

    # Create and use a draft commit message
    vim .git/draft
    git commit -eF .git/draft
