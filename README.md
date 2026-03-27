# 🌌 ptkxlord — Premium Password Manager

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Qt](https://img.shields.io/badge/Qt-6.x-41CD52.svg)](https://www.qt.io/)
[![NestJS](https://img.shields.io/badge/NestJS-Backend-E0234E.svg)](https://nestjs.com/)

**ptkxlord** — це не просто менеджер паролів. Це втілення безпеки у футуристичному дизайні **Antigravity**. Проект побудований на принципах Zero Knowledge, де ваші дані належать лише вам.

---

## ✨ Особливості (Features)

- 🔒 **Zero-Knowledge Architecture**: Майстер-пароль ніколи не покидає ваш пристрій.
- 🧪 **Military-Grade Encryption**: Використання `libsodium` (XChaCha20-Poly1305) та `SQLCipher` (AES-256).
- 🧬 **Argon2id KDF**: Найсучасніший алгоритм отримання ключів для протидії brute-force атакам.
- ☁️ **Cloud Sync**: Безпечна синхронізація зашифрованих копій через NestJS бекенд.
- 💎 **Antigravity Design**: Преміальний "скляний" UX з плавними анімаціями та градієнтами.
- ⏳ **Auto-Clear Clipboard**: Автоматичне видалення скопійованого пароля з пам'яті через 30 секунд.
- 🎲 **Ultimate Generator**: Гнучка генерація паролів з високою ентропією.

---

## 🛠 Технологічний стек (Tech Stack)

### Client (Desktop)
- **Qt 6 / C++ / QML**: Для високопродуктивного кросплатформного інтерфейсу.
- **Libsodium**: Професійна бібліотека для криптографії.
- **SQLCipher**: Повноцінне шифрування бази даних SQLite.

### Backend (Server)
- **NestJS**: Потужний Node.js фреймворк для масштабованого API.
- **Prisma ORM**: Сучасна робота з базою даних.
- **JWT & Passport**: Надійна система аутентифікації.
- **SQLite**: Легка та надійна база даних для сервера.

---

## 🚀 Як запустити (Quick Start)

### 📥 1. Підготовка бекенда
```bash
cd server
npm install
npx prisma generate
npx prisma db push
npm run dev
```
*Сервер запуститься на `http://localhost:3000`.*

### 🖥 2. Збірка клієнта (Qt)
1. Впевніться, що у вас встановлені **Qt 6**, **CMake** та бібліотека **libsodium**.
2. Відкрийте проект у **Qt Creator** або зберіть вручну:
```bash
cd client
mkdir build && cd build
cmake ..
cmake --build .
```

---

## 🛡 Безпека (Security Design)

1. **Ключ шифрування**: Генерується локально за допомогою Argon2id (Master Password + Salt).
2. **Локальне сховище**: База даних `vault.db` зашифрована SQLCipher. Без пароля це просто набір випадкових байтів.
3. **Передача даних**: На сервер передається лише зашифрований Blob та хеш для авторизації. Навіть якщо сервер зламають, зловмисники отримають лише зашифровані дані, які неможливо дешифрувати без майстер-пароля.

---

## 📸 Скріншоти (Mockups)

> Дизайн проекту натхненний естетикою `antigravity.google`, поєднуючи в собі мінімалізм та динамічні ефекти світла.

---

## 📄 Ліцензія
Проект розповсюджується під ліцензією MIT.

**Розроблено з ❤️ ptkxlord.**
