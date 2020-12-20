function open_notebook(loginId, notebookPath) {
  let login = document.getElementById(loginId).value
  if (login == "") {
    return
  }
  localStorage.setItem("riot_course_iotlab_login", login);
  let notebookUrl = `https://labs.iot-lab.info/hub/spawn?next=/user/${login}/lab/tree/${notebookPath}`
  window.open(notebookUrl, 'top')
}

function check_login(loginId, launcherId) {
  let login = document.getElementById(loginId).value
  if (login == "") {
    document.getElementById(launcherId).disabled = true
  } else {
    document.getElementById(launcherId).disabled = false
  }
}

slideshow.on('afterShowSlide', function(slide) {
  let loginId = undefined
  let launcherId = undefined
  for (let el of slide.content) {
    if (typeof el != 'string') {
      let parser = new DOMParser()
      var doc = parser.parseFromString(el.content[0], 'text/html');
      let loginElements = doc.getElementsByClassName("login");
      if (loginElements.length == 0) {
          return
      }
      loginId = loginElements[0].id
      launcherId = doc.getElementsByClassName("launcher")[0].id;
    }
  }

  if (loginId == undefined) {
      return
  }

  let login = ""
  let storedLogin = localStorage.riot_course_iotlab_login;
  if (storedLogin != undefined && storedLogin != login) {
    login = storedLogin
  }

  document.getElementById(loginId).value = login
  document.getElementById(launcherId).disabled = (login == "")
})
