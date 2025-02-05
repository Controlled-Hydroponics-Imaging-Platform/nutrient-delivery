Use this workflow when working with teams to take advantage of Pull Requests and keep the main branch clean.


## Creating and using your own branch locally:

### Create a new branch:
`git checkout -b ira`

In the future, you don't need the `-b` for this git repo, that is just to create a NEW branch if it doesn't exist in this repo.

### Switch branches:
- `git checkout main` Switches to the main branch
- `git checkout ira` Switches to the ira branch
- etc

### How to work:
Make updates on your branch and some git commits. When you're ready to merge into the main, do this:

### Push your branch up to github
`git push origin ira`

In github's web interface, **Create a PR (Pull Request)**.

NOTE: If you don't know how to do this, google `create pull request github`

**Anyone on your team** can create and submit pull requests, but be sure the **Release Manager (Repo master) manages and merges** the PR's. 
In the case of any conflicts that need to be merged via github's PR web interface, the Release Manager and anyone involved in the code conflicts work together to help merge changes and closes pull request.

### What to do after a Pull Request(s) has been merged

#### All team members need to pull updated main to their local computers. Here's how to do it:

- `git checkout main`
- `git pull` (pulls down the latest main from github, with all the changes from merged in PR's included)
- Then each team member merges the updated main code into their named branch to get the latest updates.
	- `git checkout main`
	- `git branch -D ira` (deletes your branch locally)