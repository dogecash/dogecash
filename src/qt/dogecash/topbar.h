// Copyright (c) 2019 The DogeCash developers
// Copyright (c) 2019 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef TOPBAR_H
#define TOPBAR_H

#include <QWidget>
#include "qt/dogecash/pwidget.h"
#include "qt/dogecash/lockunlock.h"
#include "amount.h"
#include <QTimer>
#include <QProgressBar>
#include "rpc/misc.h"
class DogeCashGUI;
class WalletModel;
class ClientModel;

namespace Ui {
class TopBar;
}

class TopBar : public PWidget
{
    Q_OBJECT

public:
    explicit TopBar(DogeCashGUI* _mainWindow, QWidget *parent = nullptr);
    ~TopBar();

    void showTop();
    void showBottom();

    void loadWalletModel() override;
    void loadClientModel() override;

    void openPassPhraseDialog(AskPassphraseDialog::Mode mode, AskPassphraseDialog::Context ctx);
    void encryptWallet();
    void unlockWallet();
public slots:
    void updateBalances(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance,
                        const CAmount& zerocoinBalance, const CAmount& unconfirmedZerocoinBalance, const CAmount& immatureZerocoinBalance,
                        const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance,
                        const CAmount& delegatedBalance, const CAmount& coldStakedBalance);
    void updateDisplayUnit();

    void setNumConnections(int count);
    void setNumBlocks(int count);
    void updateAutoMintStatus();
    void setStakingStatusActive(bool fActive);
    void updateStakingStatus();

signals:
    void themeChanged(bool isLight);
    void walletSynced(bool isSync);
    void onShowHideColdStakingChanged(bool show);
    /** HD-Enabled status of wallet changed (only possible during startup) */
    void hdEnabledStatusChanged(bool hdEnabled);
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void onBtnReceiveClicked();
    void onThemeClicked();
    void onBtnLockClicked();
    void lockDropdownMouseLeave();
    void lockDropdownClicked(const StateClicked&);
    void refreshStatus();
    void refreshProgressBarSize();
    void expandSync();
    void openLockUnlock();
    void onColdStakingClicked();
    void setHDStatus(bool hdEnabled);
private:
    Ui::TopBar *ui;
    LockUnlock *lockUnlockWidget = nullptr;
    QProgressBar* progressBar = nullptr;

    int nDisplayUnit = -1;
    QTimer* timerStakingIcon = nullptr;
    bool isInitializing = true;

    // pointer to global unlock context (for multithread unlock/relock)
    WalletModel::UnlockContext* pctx = nullptr;

};

#endif // TOPBAR_H
