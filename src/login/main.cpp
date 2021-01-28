
#include <frontier/frontier.h>
#include <frontier/widgets/frame.h>
#include <frontier/widgets/button.h>
#include <frontier/widgets/textinput.h>

#include <security/pam_appl.h>
#include <unistd.h>

static char** g_envp;

void startClient(char* const* envp);

class LoginApp : public Frontier::FrontierApp
{
 private:
    Frontier::FrontierWindow* m_loginWindow = nullptr;
    Frontier::TextInput* m_usernameInput = nullptr;
    Frontier::TextInput* m_passwordInput = nullptr;

    static int pamConv(int num_msg, const struct pam_message **msgm, struct pam_response **response, void *appdata_ptr);
    int pamConv(int num_msg, const struct pam_message **msgm, struct pam_response **response);

 public:
    LoginApp();
    ~LoginApp() override;

    bool init() override;

    void loginClicked([[maybe_unused]] Frontier::Widget* widget);

    bool authenticate(const std::string &username);
};

using namespace Frontier;
using namespace Geek;
using namespace std;

LoginApp::LoginApp() : FrontierApp(L"Awesome LoginApp")
{

}

LoginApp::~LoginApp() = default;

bool LoginApp::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    m_loginWindow = new FrontierWindow(this, L"Login", WINDOW_NORMAL);

    auto rootFrame = new Frame(this, false);
    auto userFrame = new Frame(this, true);
    userFrame->add(new Label(this, L"Username:"));
    userFrame->add(m_usernameInput = new TextInput(this));
    rootFrame->add(userFrame);

    auto passFrame = new Frame(this, true);
    passFrame->add(new Label(this, L"Password:"));
    passFrame->add(m_passwordInput = new TextInput(this));
    rootFrame->add(passFrame);

    m_passwordInput->setStyle("type", Value(L"password"));

    auto buttonFrame = new Frame(this, true);
    Button* loginButton;
    buttonFrame->add(loginButton = new Button(this, L"Login"));
    buttonFrame->add(new Button(this, L"Cancel"));
    rootFrame->add(buttonFrame);

    loginButton->clickSignal().connect(sigc::mem_fun(*this, &LoginApp::loginClicked));

    m_loginWindow->setContent(rootFrame);
    m_loginWindow->show();

    return true;
}

void LoginApp::loginClicked([[maybe_unused]] Frontier::Widget* widget)
{
    log(DEBUG, "loginClicked: Here!");

    wstring usernamew = m_usernameInput->getText();

    string username = Utils::wstring2string(usernamew);

    bool auth = authenticate(username);
    if (auth)
    {
        m_loginWindow->hide();
//startClient("/Users/ian/projects/awesome-desktop/cmake-build-debug/awesome-desktop");
        log(DEBUG, "loginClicked: Starting desktop!");
        startClient(g_envp);
    }
}

bool LoginApp::authenticate(const string &username)
{
    bool result = true;
#if 0
    pam_handle_t* pamh = nullptr;
    struct pam_conv conv = {
        pamConv,
        this
    };

    int res = pam_start("awesome_login", username.c_str(), &conv, &pamh);
    log(DEBUG, "loginClicked: pam_start res=%d", res);
    if (res == 0)
    {

        res = pam_authenticate(pamh, 0);
        log(DEBUG, "loginClicked: pam_authenticate res=%d", res);
        if (res == 0)
        {

            res = pam_acct_mgmt(pamh, 0);
            log(DEBUG, "loginClicked: pam_acc_mgmt res=%d", res);
            if (res == 0)
            {
                log(DEBUG, "loginClicked: Authenticated!");
                result = true;
            }
        }
        else
        {
            m_usernameInput->setStyle("background-color", Value(0xffff0000));
            m_passwordInput->setStyle("background-color", Value(0xffff0000));
            result = false;
        }

        pam_end(pamh, 0);
    }
#endif

    return result;
}

void startClient(char* const* envp)
{
    int envc = 0;
    while (envp[envc++] != nullptr);
    envc--;

    const char* env[envc + 1];
    int i;
    int envpos = 0;
    for (i = 0; i < envc; i++)
    {
        bool skip = false;
        string e = envp[i];
        int pos = e.find('=');
        if (pos != string::npos)
        {
            string name = e.substr(0, pos);
            printf("%s: %s\n", e.c_str(), name.c_str());
            if (name == "FRONTIER_ENGINE")
            {
                skip = true;
            }
        }
        if (!skip)
        {
            env[envpos++] = envp[i];
        }
    };
    env[envpos++] = "FRONTIER_ENGINE=Awesome";
    env[envpos] = nullptr;

    int pid = fork();
    if (pid == 0)
    {

        execle(
            "/Users/ian/projects/awesome-desktop/cmake-build-debug/awesome-desktop",
            "awesome-desktop",
            nullptr,
            env);

        exit(0);
    }
}


int LoginApp::pamConv(int num_msg, const struct pam_message** msgm, struct pam_response** response, void* appdata_ptr)
{
    return ((LoginApp*)appdata_ptr)->pamConv(num_msg, msgm, response);
}

int LoginApp::pamConv(int num_msg, const struct pam_message** msgm, struct pam_response** response)
{
    log(DEBUG, "pamConv: num_msg=%d", num_msg);
    int i;
    for (i = 0; i < num_msg; i++)
    {
        log(DEBUG, "pamConv: msg=%s", msgm[i]->msg);
        if (!strcmp("Password:", msgm[i]->msg))
        {
            wstring passwordw = m_passwordInput->getText();
            string password = Utils::wstring2string(passwordw);

            pam_response* reply = (pam_response*)calloc(sizeof(pam_response), 1);
            reply->resp = strdup(password.c_str());
            reply->resp_retcode = 0;
            *response = reply;
        }
    }
    return 0;
}

int main(int argc, char** argv, char* envp[])
{
    g_envp = envp;

    LoginApp loginApp;
    loginApp.init();
    loginApp.main();
    return 0;
}

