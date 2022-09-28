const btnVentiOff = document.querySelector('#btn-venti-off');
const btnVentiDown = document.querySelector('#btn-venti-down');
const btnVentiUp = document.querySelector('#btn-venti-up');

const btnsVelocity = document.querySelectorAll('.btn-velocity');

const btnLampOff = document.querySelector('#btn-lamp-off');
const btnLampOn = document.querySelector('#btn-lamp-on');

btnVentiOff.addEventListener('click', () => {
    fetch('/api/fan_control', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            state: 0,
            dir: 0
        })      
    })
    .catch(err => console.log(err));
});

btnVentiDown.addEventListener('click', () => {
    fetch('/api/fan_control', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            state: 1,
            dir: 1
        })      
    })
    .catch(err => console.log(err));
});


btnVentiUp.addEventListener('click', () => {
    fetch('/api/fan_control', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            state: 1,
            dir: 2
        })      
    })
    .catch(err => console.log(err));
});

btnsVelocity.forEach(btn => {
    btn.addEventListener('click', () => {
        const velocity = +btn.dataset.velocity;
        fetch('/api/fan_power', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                power: velocity
            })      
        })
        .catch(err => console.log(err));
    });
});

btnLampOff.addEventListener('click', () => {
    fetch('/api/lamp_control', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            state: 0
        })      
    })
    .catch(err => console.log(err));
});

btnLampOn.addEventListener('click', () => {
    fetch('/api/lamp_control', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            state: 1
        })      
    })
    .catch(err => console.log(err));
});