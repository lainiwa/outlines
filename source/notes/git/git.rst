===
Git
===

Sources:

* `Visual Git <https://marklodato.github.io/visual-git-guide/index-en.html>`_
* Cheat Sheets
    - `Oh Shit Git <https://ohshitgit.com/>`_
    - `Git and Github Cheatsheet <https://dev.to/zinox9/git-github-cheatsheet-22ok>`_
* Exercises
    - https://ohmygit.org/
* Config
    - `Limiting Upstream Tracking <https://utcc.utoronto.ca/~cks/space/blog/programming/GitUpstreamLimitedTracking>`_
* `Think Like a Git <http://think-like-a-git.net>`_
* Git Standards: https://blog.carlmjohnson.net/post/2018/git-gud/
* http://dept.cs.williams.edu/~freund/cs434/GitLab.html
* https://dev.to/henryong92/yet-another-git-cheatsheet-4gjk
* https://dev.to/lydiahallie/cs-visualized-useful-git-commands-37p1
* https://docs.gitlab.com/ee/topics/git/numerous_undo_possibilities_in_git/
* https://git-scm.com/book/ru/v2/Ветвление-в-Git-Основы-ветвления-и-слияния
* https://git-scm.com/docs/gitignore
* https://git.wiki.kernel.org/index.php/Interfaces,_frontends,_and_tools
* https://githowto.com/ru
* https://githowto.com/ru/setup
* https://habr.com/ru/post/512490/
* https://xosh.org/explain-git-in-simple-words/
* https://habr.com/ru/post/519314/
* https://learngitbranching.js.org/
* https://martinfowler.com/articles/branching-patterns.html
* https://stackoverflow.com/questions/3639342/whats-the-difference-between-git-reset-and-git-checkout
* https://utcc.utoronto.ca/~cks/space/blog/programming/GitUpstreamLimitedTracking
* https://www.atlassian.com/git/tutorials/using-branches/merge-strategy
* https://www.atlassian.com/ru/git/tutorials/merging-vs-rebasing
* Learning Git from Novice to Expert: https://news.ycombinator.com/item?id=23149700
* The Problem with Git Flow: https://news.ycombinator.com/item?id=23622071
* https://people.kernel.org/monsieuricon/what-does-a-pgp-signature-on-a-git-commit-prove
* https://symflower.com/en/company/blog/2021/git-autofixup/

.. image:: imgs/rant.png
  :width: 49%
  :target: https://youtu.be/4XpnKHJAok8


`References make commits reachable <http://think-like-a-git.net/sections/experimenting-with-git.html>`_

Equivalents
###########

.. code-block:: sh

    git pull == git fetch && git merge/rebase

    git branch -f master HEAD~ == git switch master && git reset --soft HEAD~


Snippets
########

.. code-block:: sh

    git log --oneline --graph --all
    gl --all

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
.. include:: .git_rebase_cherry_pick.rst
.. include:: .git_merge.rst
.. include:: .git_stash.rst
.. include:: .git_stacked.rst

Clean
=====

.. code-block:: sh

    # Clean untracked files (like a `rm *`)
    git clean -f|--force
    # Recursive clean of untracked files (like a `rm -r *`)
    git clean -fd

    #
    git clean ... [-n|--dry-run]

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

Merge vs Rebase
---------------
* `For rebase + merge --no-ff <https://gist.github.com/zerowidth/4684495>`__
* `Comparison with conclusion <https://blog.sourcetreeapp.com/2012/08/21/merge-or-rebase/>`__
* https://randyfay.com/comment/1093
* `Atlassian comparison <https://www.atlassian.com/git/articles/git-team-workflows-merge-or-rebase>`__

Commit Messages
---------------
* https://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html


Extensions
##########

Git DVC
-------
* https://dvc.org/doc
* too bad https://florianwinkelbauer.com/posts/2020-02-08-git-with-chunks/

::

    mkcd tstdvc

    git init
    dvc init
    git status
    git commit -m "Initialize DVC"

    dvc remote add -d myremote /tmp/dvcstore


Commits
#######
* https://www.conventionalcommits.org
* https://udacity.github.io/git-styleguide/index.html

.git directory
##############
* `Storing files in .git <https://www.arp242.net/dot-git.html>`_

::
    vim .git/todo

    vim .git/draft
    git commit -eF .git/draft
