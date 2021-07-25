===
Git
===

Sources:

* `Visual Git <https://marklodato.github.io/visual-git-guide/index-en.html>`_
* Cheat Sheets
    - `Oh Shit Git <https://ohshitgit.com/>`_
    - `Git and Github Cheatsheet <https://dev.to/zinox9/git-github-cheatsheet-22ok>`_
    - https://bitbucket.org/BitPusher16/dotfiles/src/master/refs/git/git_examples.sh
* Exercises
    - https://ohmygit.org/
    - https://learngitbranching.js.org/
* Config
    - `Limiting Upstream Tracking <https://utcc.utoronto.ca/~cks/space/blog/programming/GitUpstreamLimitedTracking>`_
* Fundamentals
    - `The Wave/Particle Duality of Git Commits <https://www.thirtythreeforty.net/posts/2020/01/the-wave-particle-duality-of-git-commits/>`_
    - https://habr.com/ru/company/badoo/blog/163853/
    - https://www.kenneth-truyers.net/2016/10/13/git-nosql-database/
* Others, used:
* `Think Like a Git <http://think-like-a-git.net>`_
* Git Standards: https://blog.carlmjohnson.net/post/2018/git-gud/
* https://dev.to/lydiahallie/cs-visualized-useful-git-commands-37p1
* http://dept.cs.williams.edu/~freund/cs434/GitLab.html
* https://dev.to/henryong92/yet-another-git-cheatsheet-4gjk
* https://docs.gitlab.com/ee/topics/git/numerous_undo_possibilities_in_git/
* https://git-scm.com/book/ru/v2/Ветвление-в-Git-Основы-ветвления-и-слияния
* https://git-scm.com/docs/gitignore
* https://git.wiki.kernel.org/index.php/Interfaces,_frontends,_and_tools
* https://githowto.com/ru
* https://githowto.com/ru/setup
* https://habr.com/ru/post/512490/
* https://xosh.org/explain-git-in-simple-words/
* https://stackoverflow.com/questions/3639342/whats-the-difference-between-git-reset-and-git-checkout
* https://www.atlassian.com/git/tutorials/using-branches/merge-strategy
* https://www.atlassian.com/ru/git/tutorials/merging-vs-rebasing
* Learning Git from Novice to Expert: https://news.ycombinator.com/item?id=23149700
* https://symflower.com/en/company/blog/2021/git-autofixup/
* https://github.com/nikitavoloboev/knowledge/blob/master/programming/version-control/git.md

.. image:: imgs/rant.png
  :width: 49%
  :target: https://youtu.be/4XpnKHJAok8


`References make commits reachable <http://think-like-a-git.net/sections/experimenting-with-git.html>`_


Snippets
########

.. code-block:: sh

    git pull == git fetch && git merge/rebase

    git branch -f master HEAD~ == git switch master && git reset --soft HEAD~

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

    # Change one word in all commits
    FILTER_BRANCH_SQUELCH_WARNING=1 \
    git filter-branch -f --tree-filter "sed -e 's#shit#flower#g' -i *.txt" 685966d6..HEAD

    # Accept pull request
    curl -sL https://github.com/nodejs/node/pull/37544.patch | git am


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


Worktree
########
* https://gaurav5430.medium.com/git-using-git-worktree-to-run-2-versions-of-the-code-at-the-same-time-1b4586315a6c
* https://dev.to/yankee/practical-guide-to-git-worktree-58o0
* https://dzone.com/articles/a-2016-git-retrospective-worktrees
* https://stackoverflow.com/questions/42457470/storage-efficient-of-a-git-clone

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
* https://martinfowler.com/articles/branching-patterns.html
* https://habr.com/ru/post/519314/

Merge vs Rebase
===============
* `For rebase + merge --no-ff <https://gist.github.com/zerowidth/4684495>`__
* `Comparison with conclusion <https://blog.sourcetreeapp.com/2012/08/21/merge-or-rebase/>`__
* https://randyfay.com/comment/1093
* `Atlassian comparison <https://www.atlassian.com/git/articles/git-team-workflows-merge-or-rebase>`__

Commit Messages
===============
* https://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html
* https://www.conventionalcommits.org
* https://udacity.github.io/git-styleguide/index.html


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


.git directory
##############
* `Storing files in .git <https://www.arp242.net/dot-git.html>`_

::

    vim .git/todo

    vim .git/draft
    git commit -eF .git/draft
