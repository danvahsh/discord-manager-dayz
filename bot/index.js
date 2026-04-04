require('dotenv').config();
const { Client, GatewayIntentBits, EmbedBuilder } = require('discord.js');
const chokidar = require('chokidar');
const fs = require('fs');
const path = require('path');

const client = new Client({ intents: [GatewayIntentBits.Guilds] });

const STATE_FILE = path.join(__dirname, 'bot-state.json');
const LEADERBOARD_FILE = process.env.LEADERBOARD_FILE_PATH;
const CHANNEL_ID = process.env.LEADERBOARD_CHANNEL_ID;

// ── State (persists leaderboard message ID across bot restarts) ────────────────

function loadState() {
    try {
        return JSON.parse(fs.readFileSync(STATE_FILE, 'utf8'));
    } catch {
        return {};
    }
}

function saveState(state) {
    fs.writeFileSync(STATE_FILE, JSON.stringify(state, null, 2));
}

// ── Embed builder ──────────────────────────────────────────────────────────────

function buildEmbed(data) {
    const sorted = [...(data.players ?? [])]
        .sort((a, b) => b.kills - a.kills || a.deaths - b.deaths)
        .slice(0, 15);

    const medals = ['🥇', '🥈', '🥉'];

    const rows = sorted.map((p, i) => {
        const kd = p.deaths > 0 ? (p.kills / p.deaths).toFixed(2) : p.kills.toFixed(2);
        const rank = medals[i] ?? `**${i + 1}.**`;
        return `${rank} **${p.name}** — ${p.kills}K / ${p.deaths}D  *(K/D: ${kd})*`;
    });

    return new EmbedBuilder()
        .setTitle('🏆 Kill Leaderboard')
        .setDescription(rows.length ? rows.join('\n') : '*No kills recorded yet this session.*')
        .setColor(0xE74C3C)
        .setFooter({ text: 'Live · Resets each server session' })
        .setTimestamp(data.lastUpdated ? new Date(data.lastUpdated) : new Date());
}

// ── Core update logic ──────────────────────────────────────────────────────────

async function updateLeaderboard() {
    if (!fs.existsSync(LEADERBOARD_FILE)) return;

    let data;
    try {
        data = JSON.parse(fs.readFileSync(LEADERBOARD_FILE, 'utf8'));
    } catch {
        // File mid-write — skip this tick
        return;
    }

    const channel = await client.channels.fetch(CHANNEL_ID).catch(() => null);
    if (!channel) {
        console.error('Could not fetch leaderboard channel. Check LEADERBOARD_CHANNEL_ID in .env');
        return;
    }

    const embed = buildEmbed(data);
    const state = loadState();

    if (state.leaderboardMessageId) {
        try {
            const msg = await channel.messages.fetch(state.leaderboardMessageId);
            await msg.edit({ embeds: [embed] });
            return;
        } catch {
            // Message was deleted — fall through to create a new one
        }
    }

    const msg = await channel.send({ embeds: [embed] });
    saveState({ leaderboardMessageId: msg.id });
    console.log(`Leaderboard message created: ${msg.id}`);
}

// ── Bot startup ────────────────────────────────────────────────────────────────

client.once('ready', () => {
    console.log(`Logged in as ${client.user.tag}`);
    console.log(`Watching: ${LEADERBOARD_FILE}`);

    updateLeaderboard();

    chokidar
        .watch(LEADERBOARD_FILE, { ignoreInitial: true, awaitWriteFinish: { stabilityThreshold: 300 } })
        .on('change', updateLeaderboard)
        .on('add', updateLeaderboard);
});

client.login(process.env.DISCORD_TOKEN);
